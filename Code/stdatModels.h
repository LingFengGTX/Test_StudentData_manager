#ifndef __MODELS_H_
#define __MODELS_H_

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<time.h>

///定义数据类型
typedef struct StudentData *StudentDataSharp;
typedef struct FileInfo *FileInfoSharp;
///定义常量
#define MEM_POOL_MAX 10
#define HEAD_LONG 124
///定义结构体

struct RegDate{
    int year;
    int mon;
    int mday;
};

struct StudentData{
    char name[50];
    char school[50];
    unsigned long int IDnumber;
    int memberID;
    struct RegDate date;
    StudentDataSharp next;
};

struct FileInfo{
    char BuildSoftware[50];
    float VersionInfo;
    char Args[50];
    ///DATE
    int year;
    int mon;
    int mday;
    ///MEMBERS
    int members;
};

///声明函数

//--:file_manage.c:--
//文件管理类
int new_file(char *FileName);
int get_fileinfo(char *FileName);
int open_file(char *FileName);
int open_fileMem(char *FileName);
int save_file(char *FileName);
int out_Data(char *OutFile);
int write_FileHead(FILE *temp_filep,int members,char *softwareInfo,char *fileArgs,float softwareVersion);
int get_HeadMembers(FILE *tempfile);
float get_HeadVersion(FILE *tempfile);
char *get_HeadAppInfo(FILE *tempfile);
char *get_HeadArgs(FILE *tempfile);

//-:data_operan.c:-
//数据操作类
int add_NewData(void);
int add_NewDataMem(void);
int clear_Data(void);
int clear_DataMem(void);
int list_Data(void);
int del_Data(void);
int del_DataMem(void);
int edit_DataDo(void);
int edit_Data(StudentDataSharp temp);
int refresh_Data(void);
void print_DataInfo(StudentDataSharp temp);
int search_Data_IDnumber(void);
int search_Data_School(void);
int search_Data_Name(void);
int search_DataDo(void);
//-:mem_manage.c:-
//内存管理类
void deal_DelData(StudentDataSharp target);
StudentDataSharp get_MemPool(void);
int get_MemMembers(void);
int clear_MemPool(void);
void get_MemInfo(void);
#endif