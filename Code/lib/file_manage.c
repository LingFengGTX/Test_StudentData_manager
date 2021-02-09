#include"stdatModels.h"

extern FILE *filep;
extern struct tm *time_cout;
extern StudentDataSharp stdatap;
extern int global_members;


int new_file(char *FileName)
 {
     int chose;
    if(access(FileName,F_OK)!=-1){    
        printf("\n--------------------------\n\
                询问:该文件已存在是否要删除重写?  \n\
                1:确认      2:取消(返回主界面)  \n\
                                                ");
        printf("(1/2 ?)>>");
        scanf("%d",&chose);
        if(chose==2){
            return 0;
        }
        //重写数据库文件
    
    }
    if((filep=fopen(FileName,"w+"))==NULL){
        perror("操作无法继续");
        return 0;
    }
    write_FileHead(filep,0,"学生学籍管理系统","该文件存储着学生的学籍信息",1.001);
    fclose(filep);
    printf("\n-----------\n\
            提示:新文件创建完成，请打开文件以编辑\n\
                                ");
    return 0;
 }

int get_fileinfo(char *FileName)
 {
    if((filep=fopen(FileName,"r"))==NULL){
        fprintf(stderr,"错误:读取文件时出错不能继续");
        return 0;
    }
    FileInfoSharp fileinfoW;
    if((fileinfoW=(FileInfoSharp)malloc(sizeof(struct FileInfo)))==NULL){
        fprintf(stderr,"申请内存失败，应用被迫退出！");
        exit(EXIT_FAILURE);
    }

    fread(fileinfoW,sizeof(struct FileInfo),1,filep);
    {
        printf("\n             \n\
                  关于此文件     \n\
                 --------------\n\
                                ");
        printf("\n创建此文件的应用程序:%s",fileinfoW->BuildSoftware);
        printf("\n应用程序版本:%.4f",fileinfoW->VersionInfo);
        printf("\n文件描述:%s",fileinfoW->Args);
        printf("\n创建日期:%d年-%d月-%d日",fileinfoW->year,fileinfoW->mon,fileinfoW->mday);
        printf("\n该文件已注册的人数:%d人",fileinfoW->members);
    }
    free(fileinfoW);
    fclose(filep);
    return 0;
 }


int open_file(char *FileName)
{
    ///该函数是用于打开已经储存好的stData.data文件，并将其读入到内存中；

    if(stdatap!=NULL){
        fprintf(stderr,"您需要清空当前的数据才能执行此操作，否则您的数据会丢失。");
        return 0;
    }
    if((filep=fopen(FileName,"r"))==NULL){
        printf("打开文件失败！");
        perror("未能打开文件");
        return 0;
    }
    ///
    //如果文件能成功被打开则读取并载入文件:
    
    //拿掉头部信息:
    int total=get_HeadMembers(filep);

    fseek(filep,HEAD_LONG,SEEK_SET);
    ///
    ///申请临时空间来存储信息
    StudentDataSharp temp;

    {//进入循环
        while(global_members<total){
            if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
                fprintf(stderr,"申请内存出错，应用被迫退出！");
                exit(EXIT_FAILURE);
            }
            fread(temp,sizeof(struct StudentData),1,filep);
            if(temp->IDnumber==0){
                printf("\n这似乎是个新文件,您可以通过 add 来录入数据最后通过 save 来保存");
                return 0;
            }
            if(ferror(filep)){
                perror("\n读取文件时出现错误:");
                exit(EXIT_FAILURE);
            }
            {//赋值
                
                //-------:定位指针:--------
                temp->next=stdatap;
                stdatap=temp;
                global_members++;
                stdatap->memberID=global_members;
            }            
        }
    }
    ///文件加载完毕，释放临时存储信息的变量以及文件信息
    fclose(filep);
    return 0;
}

//打开文件，并启用内存回收机制
int open_fileMem(char *FileName)
{
    ///该函数是用于打开已经储存好的stData.data文件，并将其读入到内存中；

    if(stdatap!=NULL){
        fprintf(stderr,"您需要清空当前的数据才能执行此操作，否则您的数据会丢失。");
        return 0;
    }
    if((filep=fopen(FileName,"r"))==NULL){
        printf("打开文件失败！");
        perror("未能打开文件");
        return 0;
    }
    ///
    //如果文件能成功被打开则读取并载入文件:
    
    //拿掉头部信息:
    int total=get_HeadMembers(filep);

    fseek(filep,HEAD_LONG,SEEK_SET);
    ///
    ///申请临时空间来存储信息
    StudentDataSharp temp;

    {//进入循环
        while(global_members<total){
            if(get_MemMembers()!=0){//检测内存池中是否还有成员
                temp=get_MemPool();
            }
            else{
                if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
                    fprintf(stderr,"申请内存出错，应用被迫退出！");
                    exit(EXIT_FAILURE);
                }
            }
            fread(temp,sizeof(struct StudentData),1,filep);
            if(temp->IDnumber==0){
                printf("\n这似乎是个新文件,您可以通过 add 来录入数据最后通过 save 来保存");
                return 0;
            }
            if(ferror(filep)){
                perror("\n读取文件时出现错误:");
                exit(EXIT_FAILURE);
            }
            {//赋值
                
                //-------:定位指针:--------
                temp->next=stdatap;
                stdatap=temp;
                global_members++;
                stdatap->memberID=global_members;
            }            
        }
    }
    ///文件加载完毕，释放临时存储信息的变量以及文件信息
    fclose(filep);
    return 0;
}

int save_file(char *FileName)
{
    if(stdatap==NULL){
        printf("\n没有可用的数据保存");
        return 0;
    }
    if(access(FileName,F_OK)!=-1){
        int chose;
        printf("\n提示:已有文件                     \n\
                如果要继续则将覆盖现有文件，您是否要继续?\n\
                1:继续            2:取消(返回主界面)  \n\
        ");
        printf("(1/2 ?)>>");
        scanf("%d",&chose);
        if(chose==2){
            return 0;
        }

    }
    
    if((filep=fopen(FileName,"wb"))==NULL){
        perror("写入文件时出错，原因:");
        return 0;
    }
    fseek(filep,write_FileHead(filep,global_members,"学生学籍管理系统","该文件存储着学生的学籍信息",1.001),SEEK_SET);
    //申请temp的变量
    StudentDataSharp temp;
    if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
        fprintf(stderr,"申请内存发生错误，应用被迫退出！");
        exit(EXIT_FAILURE);
    }
    ///遍历单链表
    temp=stdatap;
    do{
        fwrite(temp,sizeof(struct StudentData),1,filep);
        temp=temp->next;
    }while(temp!=NULL);
    free(temp);
    fclose(filep);
    printf("\n保存完成！");

    return 0;
}


int out_Data(char *OutFile)
{
    FILE *filetxt;
    int chose;
    if(stdatap==NULL){
        printf("当前数据为空，请先录入或者打开文件以进行");
        return 0;
    }
    
    if(access(OutFile,F_OK)!=-1){
        printf("\n提示:当前已有该文件          \n\
                  继续下去则会该文件，您是否要继续?    \n\
                  1:继续              2:取消(返回主界面): \n\
        ");
        printf("(1/2 ?)>>");
        scanf("%d",&chose);
        if(chose==2){
            return 0;
        }
        
    }
    ///打开文件
    if((filetxt=fopen(OutFile,"w"))==NULL){
        fprintf(stderr,"打开文件错误，应用无法导出");
        return 0;        
    }

    ///检测通过则开始打印数据
    int i=1;
    StudentDataSharp temp;
    if((temp=(StudentDataSharp)malloc(sizeof(struct StudentData)))==NULL){
        fprintf(stderr,"申请内存失败，应用被迫退出！");
        exit(EXIT_FAILURE);        
    }
    ///拷贝数据
    temp=stdatap;
    do{
        
        fprintf(filetxt,"\n---*---:第%d位同学的信息:---*---\n\
                姓名:%s                         \n\
                所在学校:%s                      \n\
                学号:%lu                        \n\
                注册日期:%d-%d-%d                \n\
                 ",i,temp->name,temp->school,temp->IDnumber,temp->date.year,temp->date.mon,temp->date.mday);
        temp=temp->next;
        fputc('\n',filetxt);
        i++;
    }while(temp!=NULL);
    free(temp);
    fclose(filetxt);
    printf("\n列出完成!");
    return 0;
}

int write_FileHead(FILE *temp_filep,int members,char *softwareInfo,char *fileArgs,float softwareVersion)
{   //该部分用于创建新文件写入文件头部时使用
    
    ///申请内存来存放临时信息
    FileInfoSharp fileinfoW;
    if((fileinfoW=(FileInfoSharp)malloc(sizeof(struct FileInfo)))==NULL){
        fprintf(stderr,"错误:系统申请内存失败，应用被迫退出");
        exit(EXIT_FAILURE);
    }
    rewind(temp_filep);
    fseek(temp_filep,0,SEEK_SET);
    ///如果打开成功的则写入头部信息
    {
        fileinfoW->VersionInfo=softwareVersion;
        strcpy(fileinfoW->BuildSoftware,softwareInfo);
        strcpy(fileinfoW->Args,fileArgs);
        ///DATE
        fileinfoW->year=time_cout->tm_year+1900;
        fileinfoW->mon=time_cout->tm_mon+1;
        fileinfoW->mday=time_cout->tm_mday;
        fileinfoW->members=members;

    }
    ///写入头部信息
    fwrite(fileinfoW,sizeof(struct FileInfo),1,temp_filep);
    ///释放内存信息
    free(fileinfoW); //释放内存
    return ftell(temp_filep);//1代表创建成功
}

int get_HeadMembers(FILE *tempfile)
{
    /*
            此函数用于获取头部信息文件中的Member值
    */
    int members_number=0;
    fseek(tempfile,0,SEEK_SET);
    
    FileInfoSharp fileoutW;
    if((fileoutW=(FileInfoSharp)malloc(sizeof(struct FileInfo)))==NULL){
        fprintf(stderr,"申请内存出错，系统被迫退出");
        exit(EXIT_FAILURE);
    }

    fread(fileoutW,sizeof(struct FileInfo),1,tempfile);
    members_number=fileoutW->members;    
    free(fileoutW);
    return members_number;
}

float get_HeadVersion(FILE *tempfile)
{
    /*
            此函数用于获取头部信息文件中的Member值
    */
    float version_number=1.0;
    fseek(tempfile,0,SEEK_SET);
    
    FileInfoSharp fileoutW;
    if((fileoutW=(FileInfoSharp)malloc(sizeof(struct FileInfo)))==NULL){
        fprintf(stderr,"申请内存出错，系统被迫退出");
        exit(EXIT_FAILURE);
    }

    fread(fileoutW,sizeof(struct FileInfo),1,tempfile);
    version_number=fileoutW->VersionInfo;    
    free(fileoutW);
    return version_number;
}

char *get_HeadAppInfo(FILE *tempfile)
{
    /*
            此函数用于获取头部信息文件中的Member值
    */
    char app_info[50];
    fseek(tempfile,0,SEEK_SET);
    
    FileInfoSharp fileoutW;
    if((fileoutW=(FileInfoSharp)malloc(sizeof(struct FileInfo)))==NULL){
        fprintf(stderr,"申请内存出错，系统被迫退出");
        exit(EXIT_FAILURE);
    }

    fread(fileoutW,sizeof(struct FileInfo),1,tempfile);
    strcpy(app_info,fileoutW->BuildSoftware);
    free(fileoutW);
    return app_info;
}

char *get_HeadArgs(FILE *tempfile)
{
    /*
            此函数用于获取头部信息文件中的Member值
    */
    char app_info[50];
    fseek(tempfile,0,SEEK_SET);
    
    FileInfoSharp fileoutW;
    if((fileoutW=(FileInfoSharp)malloc(sizeof(struct FileInfo)))==NULL){
        fprintf(stderr,"申请内存出错，系统被迫退出");
        exit(EXIT_FAILURE);
    }

    fread(fileoutW,sizeof(struct FileInfo),1,tempfile);
    strcpy(app_info,fileoutW->Args);
    free(fileoutW);
    return app_info;
}