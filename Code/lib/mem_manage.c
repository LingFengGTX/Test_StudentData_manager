#include"stdatModels.h"

extern StudentDataSharp Mem_Pool;

//此方法是用来处理要清除的数据，如果内存池成员达到最大值则会释放数据
void deal_DelData(StudentDataSharp target)
{
    if(get_MemMembers()==MEM_POOL_MAX){
        free(target);//内存池达到最大值则释放目标数据
    }
    else{
        target->next=Mem_Pool;
        Mem_Pool=target;
    }
}

//此方法取内存池中的指针，在调用此方法之前请先调用 get_MemMembers 否则将会产生意想不到的结果，例如使程序崩溃等等;
StudentDataSharp get_MemPool(void)
{
    if(Mem_Pool==NULL){
        return NULL;       //如果内存池为空，则返回NULL
    }
    ///内存池不为空则继续获取
    StudentDataSharp temp;
    temp=Mem_Pool;
    Mem_Pool=Mem_Pool->next;
    return temp;
}


//此方法是获取内存池中的成员个数。通常是和 get_MemPool 方法搭配。
int get_MemMembers(void)
{
    int numbers=0;
    
    if(Mem_Pool==NULL){
        return 0;//如果内存池为空则返回NULL
    }

    StudentDataSharp temp;
    temp=Mem_Pool;
    do{
        numbers++;
        temp=temp->next;
    }while(temp!=NULL);
    return numbers;
}

//该方法是清空内存池，删除链表数据时则会重新加入数据
int clear_MemPool(void)
{
    if(Mem_Pool==NULL){
        printf("\n内存池中无保留的数据，操作终止");
        return 0;
    }
    
    StudentDataSharp temp;
    StudentDataSharp *temp1;
    temp1=&(Mem_Pool);
    while(*(temp1)!=NULL){
        temp=*(temp1);
        *(temp1)=(*temp1)->next;
        free(temp);
    }
    printf("\n内存池清除完成！");
    return 0;
}

//获取内存池信息
void get_MemInfo(void)
{
    printf("\n             \n\
    ------------           \n\
    当前内存池信息:           \n\
    总大小:%d                \n\
    已占用:%d                \n\
    缓存大小:%lu字节         \n\
                            ",MEM_POOL_MAX,get_MemMembers(),get_MemMembers()*sizeof(struct StudentData));
}