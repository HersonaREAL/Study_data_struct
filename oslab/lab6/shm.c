#define __LIBRARY__ 
#include <linux/sched.h>
#include <linux/kernel.h>  
#include <asm/segment.h>  
#include <asm/system.h>  
#include<errno.h>
#include <linux/mm.h>
#include <unistd.h>

#define LOW_MEM 0x100000
#define PAGING_MEMORY (15*1024*1024)
#define PAGING_PAGES (PAGING_MEMORY>>12)

extern unsigned char mem_map [ PAGING_PAGES ] ;

shm g_shm[20];/*全局的共享内存*/
/*
shmget() 会新建/打开一页内存，并返回该页共享内存的 shmid（该块共享内存在操作系统内部的 id）。
所有使用同一块共享内存的进程都要使用相同的 key 参数。
如果 key 所对应的共享内存已经建立，则直接返回 shmid。
如果 size 超过一页内存的大小，返回 -1，并置 errno 为 EINVAL。
如果系统无空闲内存，返回 -1，并置 errno 为 ENOMEM。
shmflg 参数可忽略。
*/
int sys_shmget(key_t key, int size, int shmflg){
    if(size>PAGE_SIZE){
        errno=EINVAL;
        return -1;
    }
    int i;
    for(i=0;i<20;i++){
        if(g_shm[i].key==key&&g_shm[i].used==1)
            return i;
    }

   
    for(i=0;i<20;i++){
        if(g_shm[i].used!=1){
            g_shm[i].key=key;
            g_shm[i].phy=get_free_page();
            g_shm[i].used=1;
            return i;
        }
    }

    return -1;
    
}


/*
shmat() 会将 shmid 指定的共享页面映射到当前进程的虚拟地址空间中，并将其首地址返回。

如果 shmid 非法，返回 -1，并置 errno 为 EINVAL。

shmaddr 和 shmflg 参数可忽略。
*/
void *sys_shmat(int shmid, const void *shmaddr, int shmflg){
    if(shmid<0||shmid>=20||g_shm[shmid].used!=1){
        errno=EINVAL;
        return (void*)-1;
    }
   
   unsigned long brk=current->brk;
    unsigned long *page_table;
    for(;brk<0x4000000;brk+=PAGE_SIZE){
        page_table = (unsigned long *) ((brk>>20) & 0xffc);
        if(!(1&*page_table))
            continue;
        page_table = (unsigned long *) (0xfffff000 & *page_table);
        unsigned long table_off = ((current->start_code + brk) >> 12) & 0x03FF;
       
        if(1&*(page_table+(table_off<<2))){
            if(put_page(g_shm[shmid].phy,current->start_code+brk)==0)
                return (void*)-1;
            else{
                mem_map[(g_shm[shmid].phy-LOW_MEM)>>12]++;
                return (void*)brk;
                }
        }
    }
    
  /* put_page(g_shm[shmid].phy,current->brk + current->start_code);
   return (void*)current->brk;
    */
}