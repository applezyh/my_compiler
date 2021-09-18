#include<sys/time.h>

#include "temp_code.h"

char* preprocess(char* start,int *size){
    int code_size=0;
    char* old=start,*new=malloc(BUFSIZE*sizeof(char)),*ptr_new=new;
    while(*start!='\0'){
        if(*start==9||*start==10) *start=' ';
        start++;   
    }
    while(*old!='\0'){
        if(*old=='/'&&*(old+1)=='/'){old+=2;while(*old!=13&&*old!='\0') old++;continue;}
        if(*old=='/'&&*(old+1)=='*'){old+=2;while(*old!='*'&&*(old+1)!='/'&&*old!='\0') old++; old+=2;continue;}
        if(*old!=' ') {*new++=*old++;code_size++;}
        else {*new++=*old;code_size++;while(*old==' ')old++;}
    }
    *size=code_size;
    return ptr_new;
}

int main(int argc,char** argv){
    if(argc==1){printf("erro no input file!\n");return -1;}
    if(argc>2){printf("erro to much parameter!\n");return -1;}
    struct timeval starttime,endtime;
    double timeuse;
    hs_init(&id_hs);
    hs_init(&number_hs);
    *argv++;
    FILE* code=fopen(*argv,"r+");
    if(code==NULL){printf("erro can not open file %s!\n",*argv);return -1;}
    start=malloc(BUFSIZE*sizeof(char));
    memset(start,0,BUFSIZE);
    fread((void*)start,sizeof(char),BUFSIZE,code);
    int size;
    void* t=(void*)start;
    start=preprocess(start,&size);
    start[size]='\0';
    s=start;
    free(t);
    gettimeofday(&starttime,0);
    while(*start!='\0'){
        while(*start==13||*start==32) start++;
        sync_node* n;
        if((n=sync(start,&start))){
            p_resv(n,0,0);
            temp_code(n);
            print_q();
            printf("\n");
            break;
        }
        else{
            sync_node n;
            next(start,&start,&n);
        }
        while(*start==13||*start==32) start++;
    }
    start=s;
    gettimeofday(&endtime,0);
    fclose(code);
    timeuse = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    printf("//cost %fms.\n",timeuse/1000);
    return 0;
}