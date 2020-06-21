//#include<stdio.h>
#include <string.h>
#include <errno.h>
#include <asm/segment.h>

/*
int iam(const char * name);
完成的功能是将字符串参数 name 的内容拷贝到内核中保存下来。
要求 name 的长度不能超过 23 个字符。返回值是拷贝的字符数。
如果 name 的字符个数超过了 23，则返回 “-1”，并置 errno 为 EINVAL。
*/
char save_name[24];
int sys_iam(const char * name){
        int count = 0;
	    while(get_fs_byte(name+count) != '\0'){
        //内核态取数据
		 count++;
	    }
        if(count>23){
            errno=EINVAL;
            return -(EINVAL);
        }
    
    //从用户态把串复制到内核态
        int i;//非C99标准需要先声明i
       for(i = 0; i < count; i++)
			save_name[i] = get_fs_byte(name+i);
        save_name[count]='\0';
	
        printk(save_name);
        return count;
}


/*
int whoami(char* name, unsigned int size);
它将内核中由 iam() 保存的名字拷贝到 name 指向的用户地址空间中，
同时确保不会对 name 越界访存（name 的大小由 size 说明）。
返回值是拷贝的字符数。如果 size 小于需要的空间，则返回“-1”，并置 errno 为 EINVAL。
*/
int sys_whoami(char* name, unsigned int size){
        int conut = 0;
        while(save_name[conut]!='\0'){
            conut++;
        }
        if(conut>size){
            errno=EINVAL;
            return -(EINVAL);
        }
        int i;
       for(i=0; i<conut; i++){
		put_fs_byte(save_name[i],name+i);
		if(save_name[i] == '\0') break; 
	}
        return conut;
}
