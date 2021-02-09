#include"stdatModels.h"///综合头文件

///设置内存池，和文件标
StudentDataSharp stdatap=NULL;
StudentDataSharp Mem_Pool=NULL;
int global_members=0;
///设置文件指针
FILE *filep=NULL;
///时间全局变量
struct tm *time_cout;

int main(void)
{
    char chose[FILENAME_MAX];
    {
        //加载时间
        time_t t;
        time(&t);
        time_cout=localtime(&t);
    }

    char FileName[FILENAME_MAX];
    strcpy(FileName,"stData.data");


    system("cat help.txt");
    for(;;){
        printf("\n->>");
        scanf("%s",chose);
        if(strcmp(chose,"new")==0)
            new_file(FileName);
        else if(strcmp(chose,"open")==0)
            open_fileMem(FileName);
        else if(strcmp(chose,"save")==0)
            save_file(FileName);
        else if(strcmp(chose,"info")==0)
            get_fileinfo(FileName);
        else if(strcmp(chose,"add")==0)
            add_NewDataMem();
        else if(strcmp(chose,"edit")==0)
            edit_DataDo();
        else if(strcmp(chose,"search")==0)
            search_DataDo();
        else if(strcmp(chose,"del")==0)
            del_DataMem();
        else if(strcmp(chose,"list")==0)
            list_Data();
        else if(strcmp(chose,"clear")==0)
            clear_DataMem();
        else if(strcmp(chose,"out")==0)
            out_Data("StudenInfo.txt");
        else if(strcmp(chose,"about")==0)
            system("cat aboutINFO.txt");
        else if(strcmp(chose,"help")==0)
            system("cat help.txt");
        else if(strcmp(chose,"getmeminfo")==0)
            get_MemInfo();
        else if(strcmp(chose,"exit")==0)
            exit(1);
        else
            printf("\n找不到相关指令，请重试");
    }
    return 0;
}
