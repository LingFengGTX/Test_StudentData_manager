#include"stdatModels.h"

extern struct tm *time_cout;
extern StudentDataSharp stdatap;
extern int global_members;

//添加新数据
int add_NewData(void)
{
    int chose;
    printf("\n您是否要录入新数据?           \n\
            1:是        2:否(返回主界面)    \n\
        ");
    printf("(1/2 ?)>>");
    scanf("%d",&chose);
    if(chose==2){
        return 0;
    }
    ///如果输入为真，则开始录入数据;
    StudentDataSharp temp;
    if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
        fprintf(stderr,"申请内存失败，应用被迫退出");
        exit(EXIT_FAILURE);
    }
    ///准备写入数据
    {
        char name[50],school[50];
        printf("请输入学生的姓名:");
        scanf("%s",name);
        strcpy(temp->name,name);
        printf("请输入学生所在的学校:");
        scanf("%s",school);
        strcpy(temp->school,school);
        printf("请输入学生的学号:");
        scanf("%lu",&(temp->IDnumber));
        temp->date.year=time_cout->tm_year+1900;
        temp->date.mon=time_cout->tm_mon+1;
        temp->date.mday=time_cout->tm_mday;
        ///增加人数
        global_members+=1;
        temp->memberID=global_members;
        ///数据拼接
        temp->next=stdatap;
        stdatap=temp;
        refresh_Data(); //刷新成员ID
    }
    return 0;

}

//清空所有数据
int clear_Data(void)
{
    int chose;
    printf("\n询问:                 \n\
            您是否要清空当前的数据?    \n\
            (请注意:如果没有保存，数据将会被丢失!)\n\
            1:确认          2:取消(返回主界面)\n\
        ");
    printf("(1/2 ?)>>");
    scanf("%d",&chose);
    if(chose==2){
        return 0;
    }
    
    if(stdatap==NULL){
        printf("\n提示：数据池无数据，不能执行清除操作。");
        return 0;
    }
    ////如果用户确认，则将开始清除
    ///
    ///!!!Warning!!!
    ///
    StudentDataSharp temp;
    StudentDataSharp *temp1;
    temp1=&(stdatap);
    while(*(temp1)!=NULL){
        temp=*(temp1);
        *(temp1)=(*temp1)->next;
        free(temp);
    }
    global_members=0;
    printf("\n数据清除完成！");
    return 0;
}

//清空所有数据并启用内存回收机制
int clear_DataMem(void)
{
    int chose;
    printf("\n询问:                 \n\
            您是否要清空当前的数据?    \n\
            (请注意:如果没有保存，数据将会被丢失!)\n\
            1:确认          2:取消(返回主界面)\n\
        ");
    printf("(1/2 ?)>>");
    scanf("%d",&chose);
    if(chose==2){
        return 0;
    }
    
    if(stdatap==NULL){
        printf("\n提示：数据池无数据，不能执行清除操作。");
        return 0;
    }
    ////如果用户确认，则将开始清除
    ///
    ///!!!Warning!!!
    ///
    StudentDataSharp temp;
    StudentDataSharp *temp1;
    temp1=&(stdatap);
    while(*(temp1)!=NULL){
        temp=*(temp1);
        *(temp1)=(*temp1)->next;
        deal_DelData(temp);
    }
    global_members=0;
    printf("\n数据清除完成！");
    return 0;
}

//列举出所有数据
int list_Data(void)
{
    if(stdatap==NULL){
        printf("当前数据为空，请先录入或者打开文件以进行");
        return 0;
    }
    ///如果数据不为空则打印数据
    int i=1;
    StudentDataSharp temp;
    if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
        fprintf(stderr,"申请内存失败，应用被迫退出！");
        exit(EXIT_FAILURE);        
    }
    ///拷贝数据
    temp=stdatap;
    do{
        printf("\n---*---:第%d位同学的信息:---*---\n\
                姓名:%s                         \n\
                所在学校:%s                      \n\
                学号:%lu                        \n\
                注册日期:%d-%d-%d                \n\
                MemberID:%d                       \n\
                 ",i,temp->name,temp->school,temp->IDnumber,temp->date.year,temp->date.mon,temp->date.mday,temp->memberID);
        temp=temp->next;
        i++;
    }while(temp!=NULL);
    printf("\n列出完成!");
    free(temp); ///列出完成，释放指针
    return 0;
}

//该 add_NewDataMem 方法启用了内存回收机制，可以节约内存的使用
int add_NewDataMem(void)
{
    int chose;
    printf("\n您是否要录入新数据?           \n\
            1:是        2:否(返回主界面)    \n\
        ");
    printf("(1/2 ?)>>");
    scanf("%d",&chose);
    if(chose==2){
        return 0;
    }
    ///如果输入为真，则开始录入数据;
    StudentDataSharp temp;
    if(get_MemMembers()!=0){//检测内存池中是否还有成员
        temp=get_MemPool();
    }
    else{
        if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
            fprintf(stderr,"申请内存失败，应用被迫退出");
            exit(EXIT_FAILURE);
        }
    }
    ///准备写入数据
    {
        char name[50],school[50];
        printf("请输入学生的姓名:");
        scanf("%s",name);
        strcpy(temp->name,name);
        printf("请输入学生所在的学校:");
        scanf("%s",school);
        strcpy(temp->school,school);
        printf("请输入学生的学号:");
        scanf("%lu",&(temp->IDnumber));
        temp->date.year=time_cout->tm_year+1900;
        temp->date.mon=time_cout->tm_mon+1;
        temp->date.mday=time_cout->tm_mday;
        ///增加人数
        global_members+=1;
        temp->memberID=global_members;
        ///数据拼接
        temp->next=stdatap;
        stdatap=temp;
        refresh_Data(); //刷新成员ID
    }
    return 0;

}


//删除指定成员
int del_Data(void)
{
    int targetID;
    printf("\n提示:如果忘记了 MemberID 您可以键入0返回主界面然后键入9查看");
    printf("\n请输入目标 MemberID:");
    scanf("%d",&targetID);
    if(targetID==0){
        //用户确认返回主界面
        return 0;
    }
    StudentDataSharp tempSharp=NULL;
    StudentDataSharp tempSharp1=NULL;
    tempSharp=stdatap;
    while(tempSharp!=NULL){
        if(tempSharp->memberID==targetID){
            //链接成员
            if(tempSharp1!=NULL){
                tempSharp1->next=tempSharp->next;
            }
        else{
            stdatap=tempSharp->next;
            }
            deal_DelData(tempSharp);
            refresh_Data(); //刷新成员ID
            return 0;
        }
        tempSharp1=tempSharp;
        tempSharp=tempSharp->next;
    }
    printf("\n没有找到目标ID，请重试。");
    return 0;
}

//删除指定成员,启用内存回收机制
int del_DataMem(void)
{
    int targetID;
    printf("\n提示:如果忘记了 MemberID 您可以键入0返回主界面然后键入9查看");
    printf("\n请输入目标 MemberID:");
    scanf("%d",&targetID);
    if(targetID==0){
        //用户确认返回主界面
        return 0;
    }
    StudentDataSharp tempSharp=NULL;
    StudentDataSharp tempSharp1=NULL;
    tempSharp=stdatap;
    while(tempSharp!=NULL){
        if(tempSharp->memberID==targetID){
            //链接成员
            if(tempSharp1!=NULL){
                tempSharp1->next=tempSharp->next;
            }
        else{
            stdatap=tempSharp->next;
            }
            deal_DelData(tempSharp);
            refresh_Data(); //刷新成员ID
            return 0;
        }
        tempSharp1=tempSharp;
        tempSharp=tempSharp->next;
    }
    printf("\n没有找到目标ID，请重试。");
    return 0;
}

//编辑方法的入口
int edit_DataDo(void)
{
    int TargetID;
    printf("\n提示:如果忘记了 MemberID 您可以键入0返回主界面然后键入9查看");
    printf("\n请输入目标 MemberID:");
    scanf("%d",&TargetID); 
    if(TargetID==0){
        //用户确认返回主界面
        return 0;
    }
    //开始搜索
    StudentDataSharp temp=NULL;
    temp=stdatap;
    while(temp!=NULL){
        if(temp->memberID==TargetID){
            edit_Data(temp);
            return 0;
        }
        temp=temp->next;
    }    
    printf("\n没有找到目标ID，请重试。");
    return 0;
}

//此方法将其中的目标值修改
int edit_Data(StudentDataSharp temp)
{
    char name[50],school[50];
    printf("请输入学生的姓名:");
    scanf("%s",name);
    strcpy(temp->name,name);
    printf("请输入学生所在的学校:");
    scanf("%s",school);
    strcpy(temp->school,school);
    printf("请输入学生的学号:");
    scanf("%lu",&(temp->IDnumber));
    temp->date.year=time_cout->tm_year+1900;
    temp->date.mon=time_cout->tm_mon+1;
    temp->date.mday=time_cout->tm_mday;
    //录入完毕
    return 0;
}

//此方法是刷新链表成员的ID信息，用于删减，添加时使用。
int refresh_Data(void)
{
    global_members=0; //初始化总人数
    StudentDataSharp temp=NULL;
    temp=stdatap;
    while(temp!=NULL){
        global_members++;
        temp->memberID=global_members;
        temp=temp->next;
    }
    return 0;
}

int search_DataDo(void)
{
    if(stdatap==NULL){
        printf("\n目前没有数据，请录入或打开文件后再试。");
        return 0;
    }
    int chose;
    printf("\n-查找选项-");
    printf("\n1:按照姓名查找");
    printf("\n2:按照学校名称查找");
    printf("\n3:按照学号查找");
    printf("\n请选择您要查找的条件:");
    scanf("%d",&chose);
    switch(chose){
        case 1:search_Data_Name();break;
        case 2:search_Data_School();break;
        case 3:search_Data_IDnumber();break;
        default:printf("\n-*-:没有您要查找的信息,请重试:-*-");break;
    }
    return 0;
}

int search_Data_Name(void)
{
    char Target_name[50];
    StudentDataSharp temp=NULL;
    int chose;
    temp=stdatap;
    printf("\n请输入您要查找的姓名:");
    scanf("%s",Target_name);
    while(temp!=NULL){
        if(strcmp(temp->name,Target_name)==0){
            printf("\n查找到了:%s的信息:",Target_name);
            print_DataInfo(temp);
            printf("\n-----:是否要继续向下寻找?:----- \n\
                    1:继续          2:终止(返回主界面)\n\
            ");
            scanf("%d",&chose);
            if(chose==2){
                return 0;
            }
        }
        temp=temp->next;
    }
    printf("\n找不到姓名为:%s的信息,搜索停止",Target_name);
    return 0;
}
int search_Data_School(void)
{
    char Target_name[50];
    StudentDataSharp temp=NULL;
    int chose;
    temp=stdatap;
    printf("\n请输入您要查找的学校名称:");
    scanf("%s",Target_name);
    while(temp!=NULL){
        if(strcmp(temp->school,Target_name)==0){
            printf("\n查找到了:%s的信息:",Target_name);
            print_DataInfo(temp);
            printf("\n-----:是否要继续向下寻找?:----- \n\
                    1:继续          2:终止(返回主界面)\n\
            ");
            scanf("%d",&chose);
            if(chose==2){
                return 0;
            }
        }
        temp=temp->next;
    }
    printf("\n找不到所在学校名称为:%s的信息,搜索停止",Target_name);
    return 0;
}

int search_Data_IDnumber(void)
{
    unsigned long int Target_number;
    StudentDataSharp temp=NULL;
    int chose;
    temp=stdatap;
    printf("\n请输入您要查找的ID:");
    scanf("%lu",&Target_number);
    while(temp!=NULL){
        if(Target_number==temp->IDnumber){
            printf("\n查找到了:%lu的信息:",Target_number);
            print_DataInfo(temp);
            printf("\n-----:是否要继续向下寻找?:----- \n\
                    1:继续          2:终止(返回主界面)\n\
            ");
            scanf("%d",&chose);
            if(chose==2){
                return 0;
            }
        }
        temp=temp->next;
    }
    printf("\n找不到ID为:%lu的信息,搜索停止",Target_number);
    return 0;
}

void print_DataInfo(StudentDataSharp temp){
    printf("\n  姓名:%s                         \n\
                所在学校:%s                      \n\
                学号:%lu                        \n\
                注册日期:%d-%d-%d                \n\
                MemberID:%d                       \n\
                 ",temp->name,temp->school,temp->IDnumber,temp->date.year,temp->date.mon,temp->date.mday,temp->memberID);
}