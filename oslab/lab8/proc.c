#include <errno.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <asm/segment.h>
#include <asm/system.h>
#include <stdarg.h>



char proc_buff[4096]={'\0'};

int sprintf(char *buf, const char *fmt, ...)
{
    va_list args; int i;
    va_start(args, fmt);
    i=vsprintf(buf, fmt, args);
    va_end(args);
    return i;
}

/*快速算出32位中有多少个1*/
int count_bits(int x)
{
  register int xx=x;
  xx=xx-((xx>>1)&0x55555555);
  xx=(xx&0x33333333)+((xx>>2)&0x33333333);
  xx=(xx+(xx>>4))&0x0f0f0f0f;
  xx=xx+(xx>>8);
  return (xx+(xx>>16)) & 0xff;
}


/*
inode->i_zone[0]，这就是 mknod() 时指定的 dev ——设备编号

buf，指向用户空间，就是 read() 的第二个参数，用来接收数据

count，就是 read() 的第三个参数，说明 buf 指向的缓冲区大小

&file->f_pos，f_pos 是上一次读文件结束时“文件位置指针”的指向。
这里必须传指针，因为处理函数需要根据传给 buf 的数据量修改 f_pos 的值。
*/
int proc_read(int dev,char *buf,int count,long *pos){
    long pos_offset=*pos;
    long buf_offset=*pos;
    int i,j;
    int total_block,free_block,used_block;
    int p_32;
    struct task_struct **p;
    struct super_block * sb;
    struct buffer_head * bh;

    if(buf_offset==0)
        /*psinfo*/
        if(dev==0){
        /*进程信息存入buff*/
            cli();
            buf_offset=sprintf(proc_buff,"%s","pid\tstate\tfather\tcounter\tstart_time\n");
            for(p = &LAST_TASK ; p > &FIRST_TASK ; --p)
                if(*p)
                    buf_offset+=sprintf(proc_buff+buf_offset,"%d\t%d\t%d\t%d\t%d\n",(*p)->pid,(*p)->state,(*p)->father,(*p)->counter,(*p)->start_time);
            proc_buff[buf_offset]='\0';
            sti();
        }
        /*hdinfo*/
        else if(dev==1){
            cli();
            sb=get_super(current->root->i_dev);
            total_block=sb->s_nzones;
            used_block=0;
        
            for(i=0; i<sb->s_zmap_blocks; i++){
                    bh = sb->s_zmap[i];
                    for(j=0;j<1024;j+=4){
                        /*每个逻辑块视图共有1024个块*/
                        /*每四块组成一个int，一次性算出1的个数*/
                        p_32=bh->b_data[j];
                        p_32=(p_32<<8)+bh->b_data[j+1];
                        p_32=(p_32<<8)+bh->b_data[j+2];
                        p_32=(p_32<<8)+bh->b_data[j+3];
                        used_block+=count_bits(p_32);
                }
            }
            used_block+=sb->s_firstdatazone;

            buf_offset=sprintf(proc_buff,"total_block:%d\n",total_block);
            buf_offset+=sprintf(proc_buff+buf_offset,"used_block:%d\n",used_block);
            buf_offset+=sprintf(proc_buff+buf_offset,"free_block:%d\n",total_block-used_block);
            buf_offset+=sprintf(proc_buff+buf_offset,"total_inode:%d\n",sb->s_ninodes);
            proc_buff[buf_offset]='\0';
            sti();
        }
        else
            return -EINVAL;


    /*放入用户态buff*/
    for(i=0;i<count;i++){
        if(proc_buff[i+pos_offset]=='\0')
            break;
        put_fs_byte(proc_buff[i+pos_offset],buf+i);
    }
    
    *pos+=i;
    if(i==0)
        *pos=0;
    return i;
    
}