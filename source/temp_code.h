#include "sync_analy.h"

#define LOD 300
#define STOR 301
#define BL 307
#define JMP 308
#define LABLE 309
#define MOV 310
#define PUSH 311
#define POP 312
int lable=0;
int num_of_para=0;
typedef struct func_sy
{
    /* data */
    char* name;
    int name_size;
    int ret_type;
}func_sy;
typedef struct id_sy
{
    /* data */
    char* name;
    int name_size;
    bool isconst;
    int stack_index;
    int block_level;
    bool isglob;
    char* value;
}id_sy;
typedef struct temp_sy
{
    /* data */
    char* name;
    int name_size;
}temp_sy;

typedef struct q
{
    /* data */
    int op;
    char* re;
    char* args1;
    char* args2;
}q;


int q_index=0;
int stack_len=0;
int block_level=0;
int is_if=0;
int func_index=0;
int lab_index=0;
int lab_id=0;
int id_index=1;
int num_number=0;
int count_para=0;
int temp_index=0;
int temp_name=0;
int ret_index=0;

int ret_link[100];
func_sy func_table[100];
q q_table[10000];
char* lable_table[100];
id_sy id_table[100];
temp_sy temp_table[1000];

char* get_lab_name(){
    lable_table[lab_index]=(char*)malloc(sizeof(char)*10);
    memset(lable_table[lab_index],0,sizeof(char)*10);
    sprintf(lable_table[lab_index],".L%d",lab_id++);
    return lable_table[lab_index++];
}

int count_outvar(){
    int i;
    int count=0;
    for(i=1;i<id_index;i++){
        if(id_table[i].block_level<block_level){
            count++;
        }
    }
    return count;
}

void print_op(int op){
    switch (op)
    {
    case LOD:
        printf("ldr");
        break;
    case STOR:
        printf("str");
        break;
    case BL:
        printf("bl");
        break;
    case JMP:
        printf("b");
        break;
    case LABLE:
        printf("LABLE");
        break;
    case MOV:
        printf("mov");
        break;
    case PUSH:
        printf("push");
        break;
    case POP:
        printf("pop");
        break;
    case ADD:
        printf("add");
        break;
    case SUB:
        printf("sub");
        break;
    case MUL:
        printf("mul");
        break;
    case DIV:
        printf("div");
        break;
    case MOD:
        printf("mod");
        break;
    case RET:
        printf("RET");
        break;
    case CMP:
        printf("cmp");
        break;
    case TEQ:
        printf("teq");
        break;
    case BEQ:
        printf("beq");
        break;
    case BNE:
        printf("bne");
        break;
    case FUNC:
        printf("FUNC");
        break;
    case BLE:
        printf("ble");
        break;
    case BGE:
        printf("bge");
        break;
    case STR:
        printf("str");
        break;
    case MOVW:
        printf("movw");
        break;
    case MOVT:
        printf("movt");
        break;
    default:
        printf("%d",op);
        break;
    }
}

int get_size(char* a){
    if(a==NULL) return 0;
    int i=0;
    while(a[i]!='\0'){
        i++;
    }
    return i;
}

void print_id();
void print_glob();
void print_q(){
    print_id();
    printf("\n");
    print_glob();
    int blank=0;
    int i;
    char code[1000];
    for(i=0;i<q_index;i++){
        if(q_table[i].op==FUNC){
            if(q_table[i].re==NULL){
                q_table[i].re="\0";
            }
            if(q_table[i].args1==NULL){
                q_table[i].args1="\0";
            }
            if(q_table[i].args2==NULL){
                q_table[i].args2="\0";
            }
            printf("%s:\n",q_table[i].args1);
            continue;
        }
        if(q_table[i].op==LABLE){
            if(q_table[i].re==NULL){
                q_table[i].re="\0";
            }
            if(q_table[i].args1==NULL){
                q_table[i].args1="\0";
            }
            if(q_table[i].args2==NULL){
                q_table[i].args2="\0";
            }
            printf("%s:\n",q_table[i].args1);
            continue;
        }
        blank=4;
        char* a=(char*)malloc(sizeof(char)*blank);
        memset(a,32,sizeof(char)*blank);
        printf("%s",a);
        sprintf(code,"%s",a);
        q tq=q_table[i];
        if(tq.op==PUSH||tq.op==POP){
            print_op(tq.op);
            if(tq.op==PUSH) printf(" {%s}\n",tq.args1);
            else printf(" {%s}\n",tq.re);
        }
        if(tq.op==ADD||tq.op==SUB||tq.op==MUL||tq.op==DIV){
            print_op(tq.op);
            printf(" %s, %s, %s\n",tq.re,tq.args1,tq.args2);
        }
        if(tq.op==STR||tq.op==LOD){
            print_op(tq.op);
            if(tq.op==STR){
                printf(" %s, %s\n",tq.args1,tq.re);
            }
            if(tq.op==LOD){
                printf(" %s, %s\n",tq.re,tq.args1);
            }
        }
        if(tq.op==MOV||tq.op==MOVT||tq.op==MOVW){
            print_op(tq.op);
            printf(" %s, %s\n",tq.re,tq.args1);
        }
        if(tq.op==BL){
            print_op(tq.op);
            printf(" %s\n",tq.args1);
        }
        if(tq.op==CMP){
            print_op(tq.op);
            printf(" %s, %s\n",tq.args1,tq.args2);
        }
        if(tq.op==BNE){
            print_op(tq.op);
            printf(" %s\n",tq.args1);
        }
        if(tq.op==BLE){
            print_op(tq.op);
            printf(" %s\n",tq.args1);
        }
        if(tq.op==BGE){
            print_op(tq.op);
            printf(" %s\n",tq.args1);
        }
        if(tq.op==BEQ){
            print_op(tq.op);
            printf(" %s\n",tq.args1);
        }
        if(tq.op==JMP){
            print_op(tq.op);
            printf(" %s\n",tq.args1);
        }
    }
}

int find_func(char* name,int size){
    int i;
    for(i=func_index-1;i>-1;i--){
        if(size==func_table[i].name_size&&compare_arry(func_table[i].name,name,size)){
            return i;
        }
    }
    return -1;
}

void print_id(){
    int i;
    printf(".section .data\n");
    for(i=1;i<id_index;i++){
        if(id_table[i].isglob){
            printf("%s:\n    .word %s\n",id_table[i].name,(id_table[i].value)+1);
        }
    }
    printf("\n");
}

int find_id(char* name,int size){
    int i;
    for(i=id_index-1;i>-1;i--){
        if(size==id_table[i].name_size&&compare_arry(id_table[i].name,name,size)){
            return i;
        }
    }
    return -1;
}

char* get_temp_name(){
    int count=0;
    int i;
    if(temp_index==0){
        char* t=(char*)malloc(sizeof(char)*4);
        memset(t,0,4*sizeof(char));
        sprintf(t," %d",count);
        t[0]='r';
        return t;
    }
    for(;;count++){ 
        char* t=(char*)malloc(sizeof(char)*4);
        memset(t,0,4*sizeof(char));
        sprintf(t," %d",count);
        t[0]='r';
        bool ok=1;
        for(i=0;temp_table[i].name!=0;i++){
            if(temp_table[i].name[0]=='r'){
                int j;    
                int c=0;           
                for(j=0;j<4;j++){
                    if(t[j]==temp_table[i].name[j]) {c++;}
                }
                if(c==4){ok=0;}
            }
        }
        if(ok) return t;
        else free(t);
    }
    return NULL;
}

int find_temp(char* name,int size){
    int i;
    for(i=temp_index-1;i>-1;i--){
        if(size==temp_table[i].name_size&&compare_arry(temp_table[i].name,name,size)){
            return i;
        }
    }
    return -1;
}

void print_temp(){
    int i;
    if(temp_index==0){
        printf("%d",temp_index);
    }
    else{
        printf("%d",temp_index);
        for(i=0;i<temp_index;i++){
            printf("%s ",temp_table[i].name);
        }
    }
    printf("\n");
}

void print_glob(){
    int i;
    for(i=0;i<func_index;i++){
        printf("    .global %s\n",func_table[i].name);
    }
}

void temp_code(sync_node* n){
    if(n==NULL||n->empty) return;
    else{
        linknode ln;
    ln.node=n;
    //print_type(&ln);
    //printf("\n");
    //print_id();
        switch(n->type){
            case EXP:
                temp_code(n->child[0]);
                break;
            case ADDEXP:
                if(n->child[1]->empty){temp_code(n->child[0]);}
                if(!n->child[1]->empty){ 
                    temp_code(n->child[0]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_table[q_index++].op=PUSH;
                    stack_len++;
                    temp_index--;
                    temp_code(n->child[1]->child[1]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    char* a=get_temp_name();
                    q_table[q_index].re=a;
                    q_table[q_index++].op=POP;
                    stack_len--;
                    q_table[q_index].args2=temp_table[temp_index-1].name;
                    q_table[q_index].args1=a;
                    q_table[q_index].re=temp_table[temp_index-1].name;
                    q_table[q_index++].op=n->child[1]->child[0]->tk.attribute;
                    temp_code(n->child[1]);
                }
                break;
            case MULEXP:
                if(n->child[1]->empty){temp_code(n->child[0]);}
                if(!n->child[1]->empty){ 
                    temp_code(n->child[0]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_table[q_index++].op=PUSH;
                    stack_len++;
                    temp_index--;
                    temp_code(n->child[1]->child[1]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    char* a=get_temp_name();
                    q_table[q_index].re=a;
                    q_table[q_index++].op=POP;
                    stack_len--;
                    q_table[q_index].args2=temp_table[temp_index-1].name;
                    q_table[q_index].args1=a;
                    q_table[q_index].re=temp_table[temp_index-1].name;
                    q_table[q_index++].op=n->child[1]->child[0]->tk.attribute;
                    temp_code(n->child[1]);
                }
                break;
            case ADDEXP1:
                if(!n->child[2]->empty){
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_table[q_index++].op=PUSH;
                    stack_len++;
                    temp_index--;
                    temp_code(n->child[2]->child[1]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    char* a=get_temp_name();
                    q_table[q_index].re=a;
                    q_table[q_index++].op=POP;
                    stack_len--;
                    q_table[q_index].args2=temp_table[temp_index-1].name;
                    q_table[q_index].args1=a;
                    q_table[q_index].re=temp_table[temp_index-1].name;
                    q_table[q_index++].op=n->child[2]->child[0]->tk.attribute;
                    temp_code(n->child[2]);
                }
                break;
            case MULEXP1:
                if(!n->child[2]->empty){
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_table[q_index++].op=PUSH;
                    stack_len++;
                    temp_index--;
                    temp_code(n->child[2]->child[1]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=MOV;
                    }
                    char* a=get_temp_name();
                    q_table[q_index].re=a;
                    q_table[q_index++].op=POP;
                    stack_len--;
                    q_table[q_index].args2=temp_table[temp_index-1].name;
                    q_table[q_index].args1=a;
                    q_table[q_index].re=temp_table[temp_index-1].name;
                    q_table[q_index++].op=n->child[2]->child[0]->tk.attribute;
                    temp_code(n->child[2]);
                }
                break;
            case UNARYEXP:
                if(n->child[0]->tk.attribute==ADD){
                    temp_code(n->child[1]);
                    break;
                }
                if(n->child[0]->tk.attribute==SUB){
                    temp_code(n->child[1]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        char* a=get_temp_name();
                        q_table[q_index].re=a;
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        temp_table[temp_index-1].name=a;
                        q_table[q_index++].op=MOV;
                    }
                    char* a=get_temp_name();
                    q_table[q_index].re=a;
                    q_table[q_index].args1="#0";
                    q_table[q_index++].op=MOV;
                    q_table[q_index].re=temp_table[temp_index-1].name;
                    q_table[q_index].args1=a;
                    q_table[q_index].args2=temp_table[temp_index-1].name;
                    q_table[q_index++].op=SUB;
                    break;
                }
                if(n->index==3){
                    temp_code(n->child[1]);
                    break;
                }
                if(n->index==2){
                    if(n->child[1]->empty){
                        int i;
                        if((i=find_id(n->child[0]->tk.id->data,n->child[0]->tk.id->data_size))!=-1){
                            if(id_table[i].isglob){
                                temp_table[temp_index].name=get_temp_name();
                                q_table[q_index].re=temp_table[temp_index++].name;
                                q_table[q_index].args1=n->child[0]->tk.id->data;
                                q_table[q_index++].op=LOD;
                            }
                            else{
                                temp_table[temp_index].name=get_temp_name();
                                q_table[q_index].re=temp_table[temp_index++].name;
                                char* a=(char*)malloc(sizeof(char)*10);
                                memset(a,0,sizeof(char)*10);
                                sprintf(a,"[sp, #%d]",(stack_len-id_table[i].stack_index-1)*4);
                                q_table[q_index].args1=a;
                                q_table[q_index++].op=LOD;
                            }
                        }
                        else{
                            printf("erro var %s not defined\n",n->child[0]->tk.id->data);
                        }
                    }
                    else{
                        int f;
                        if((f=find_func(n->child[0]->tk.id->data,n->child[0]->tk.id->data_size))!=-1){
                                int i;
                                for(i=temp_index-1;i>-1;i--){
                                    if(temp_table[i].name[0]=='r'){
                                        q_table[q_index].args1=temp_table[i].name;
                                        q_table[q_index++].op=PUSH;
                                        stack_len++;
                                    }  
                                }
                                int id_stack_top=id_index;
                                int t_temp=temp_index;
                                temp_code(n->child[1]);
                                temp_index=t_temp;
                                q_table[q_index].args1=n->child[0]->tk.id->data;
                                q_table[q_index++].op=BL;
                                id_index=id_stack_top;
                                if(func_table[f].ret_type!=VOID){
                                    stack_len++;
                                    temp_table[temp_index].name=get_temp_name();
                                    q_table[q_index].re=temp_table[temp_index++].name;
                                    q_table[q_index++].op=POP;
                                    stack_len--;
                                }
                                else{
                                    temp_index++;
                                }
                                if(count_para!=0){
                                    q_table[q_index].re="sp";
                                    char* a=(char*)malloc(sizeof(char)*10);
                                    memset(a,0,sizeof(char)*10);
                                    sprintf(a,"#%d",count_para*4);
                                    q_table[q_index].args1="sp";
                                    q_table[q_index].args2=a;
                                    q_table[q_index++].op=ADD;
                                    stack_len-=count_para;
                                }
                                count_para=0;
                                for(i=0;i<temp_index-1;i++){
                                    if(temp_table[i].name[0]=='r'){
                                        q_table[q_index].re=temp_table[i].name;
                                        q_table[q_index++].op=POP;
                                        stack_len--;
                                    }
                                }
                        }
                        else{
                            printf("erro func %s not defined\n",n->child[0]->tk.id->data);
                        }
                    }
                }
                if(n->index==1){
                    char* a=(char*)malloc(sizeof(char)*10);
                    memset(a,0,sizeof(char)*10);
                    unsigned int t_number=(unsigned int)atoi(n->child[0]->tk.number->data);
                    if((t_number>>16)>0){
                        temp_table[temp_index].name=get_temp_name();
                        q_table[q_index].re=temp_table[temp_index].name;
                        q_table[q_index].args1=(char*)malloc(sizeof(char)*10);
                        sprintf(q_table[q_index].args1,"#%d",(t_number<<16)>>16);
                        q_table[q_index++].op=MOVW;
                        q_table[q_index].re=temp_table[temp_index++].name;
                        q_table[q_index].args1=(char*)malloc(sizeof(char)*10);
                        sprintf(q_table[q_index].args1,"#%d",(t_number>>16));
                        q_table[q_index++].op=MOVT;
                    }
                    else{
                        sprintf(a,"#%s",n->child[0]->tk.number->data);
                        temp_table[temp_index++].name=a;
                    }
                }
                break;
            case FUNCRPARAM:
                if(n->child[1]->empty){
                    int t_temp=temp_index;
                    temp_code(n->child[0]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index].re=get_temp_name();
                        temp_table[temp_index-1].name=q_table[q_index].re;
                        q_table[q_index++].op=MOV;
                    }
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_table[q_index++].op=PUSH;
                    stack_len++;
                    count_para++;
                    temp_index=t_temp;
                }
                else{
                    temp_code(n->child[0]);
                    if(temp_table[temp_index-1].name[0]!='r'){
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index].re=get_temp_name();
                        temp_table[temp_index-1].name=q_table[q_index].re;
                        q_table[q_index++].op=MOV;
                    }
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_table[q_index++].op=PUSH;
                    stack_len++;
                    temp_index-=1;
                    count_para++;
                    temp_code(n->child[1]);
                }
                break;
            case IDPREFIX:
                if(!n->child[1]->empty) temp_code(n->child[1]);
                break;
            case COND:
                if(n->index==1) temp_code(n->child[0]);
                if(n->index==4) temp_code(n->child[2]);
                break;
            case LOREXP:
                if(n->child[1]->empty) temp_code(n->child[0]);
                if(!n->child[1]->empty){
                    int t=lab_index;
                    char* a=get_lab_name();
                    lable_table[lab_index++]=lable_table[t-1];
                    temp_code(n->child[0]);
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=a;
                    lab_index=t;
                    temp_code(n->child[1]);
                }
                break;
            case LOREXP1:
                if(n->child[2]->empty) {
                    int t=lab_index;
                    lable_table[lab_index++]=lable_table[t-2];
                    lable_table[lab_index++]=NULL;
                    temp_code(n->child[1]);
                    lab_index=t;
                }
                if(!n->child[2]->empty){
                    int t=lab_index;
                    char* a=get_lab_name();
                    lable_table[lab_index++]=lable_table[t-1];
                    temp_code(n->child[1]);
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=a;
                    lab_index=t;
                    temp_code(n->child[2]);
                }
                break;
            case LANDEXP:
                if(n->child[1]->empty) temp_code(n->child[0]);
                if(!n->child[1]->empty){
                    int t=lab_index;
                    lable_table[lab_index++]=lable_table[t-2];
                    char* a=get_lab_name();
                    temp_code(n->child[0]);
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=a;
                    lab_index=t;
                    temp_code(n->child[1]);
                }
                break;
            case LANDEXP1:
                if(n->child[2]->empty) {
                    int t=lab_index;
                    lable_table[lab_index++]=NULL;
                    lable_table[lab_index++]=lable_table[t-1];
                    temp_code(n->child[1]);
                    lab_index=t;
                }
                if(!n->child[2]->empty){
                    int t=lab_index;
                    lable_table[lab_index++]=lable_table[t-2];
                    char* a=get_lab_name();
                    temp_code(n->child[1]);
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=a;
                    lab_index=t;
                    temp_code(n->child[2]);
                }
                break;
            case RELEXP:
                if(n->child[1]->child[0]->tk.attribute==EQL){
                    temp_code(n->child[0]);
                    temp_code(n->child[1]->child[1]);
                    q_table[q_index].op=CMP;
                    q_table[q_index].args1=temp_table[temp_index-2].name;
                    q_table[q_index++].args2=temp_table[temp_index-1].name;
                    temp_index-=2;
                    if(lable_table[lab_index-2]!=NULL){
                        q_table[q_index].op=BNE;
                        q_table[q_index++].args1=lable_table[lab_index-2];
                    }
                    else{
                        q_table[q_index].op=BEQ;
                        q_table[q_index++].args1=lable_table[lab_index-1];
                    }
                }
                if(n->child[1]->child[0]->tk.attribute==UEQL){
                    temp_code(n->child[0]);
                    temp_code(n->child[1]->child[1]);
                    q_table[q_index].op=CMP;
                    q_table[q_index].args1=temp_table[temp_index-2].name;
                    q_table[q_index++].args2=temp_table[temp_index-1].name;
                    temp_index-=2;
                    if(lable_table[lab_index-2]!=NULL){
                        q_table[q_index].op=BEQ;
                        q_table[q_index++].args1=lable_table[lab_index-2];
                    }
                    else{
                        q_table[q_index].op=BNE;
                        q_table[q_index++].args1=lable_table[lab_index-1];
                    }
                }
                if(n->child[1]->child[0]->tk.attribute==GRET){
                    temp_code(n->child[0]);
                    temp_code(n->child[1]->child[1]);
                    if(lable_table[lab_index-2]!=NULL){
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2=temp_table[temp_index-1].name;
                        q_table[q_index].op=BLE;
                        q_table[q_index++].args1=lable_table[lab_index-2];
                        temp_index-=2;
                    }
                    else{
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=SUB;
                        q_table[q_index].re=temp_table[temp_index-2].name;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2="#1";
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2=temp_table[temp_index-1].name;
                        temp_index-=2;
                        q_table[q_index].op=BGE;
                        q_table[q_index++].args1=lable_table[lab_index-1];
                    }
                }
                if(n->child[1]->child[0]->tk.attribute==UGRET){
                    temp_code(n->child[0]);
                    temp_code(n->child[1]->child[1]);
                    if(lable_table[lab_index-2]!=NULL){
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2=temp_table[temp_index-1].name;
                        q_table[q_index].op=BGE;
                        q_table[q_index++].args1=lable_table[lab_index-2];
                        temp_index-=2;
                    }
                    else{
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=ADD;
                        q_table[q_index].re=temp_table[temp_index-2].name;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2="#1";
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2=temp_table[temp_index-1].name;
                        temp_index-=2;
                        q_table[q_index].op=BGE;
                        q_table[q_index++].args1=lable_table[lab_index-1];
                    }
                }
                if(n->child[1]->child[0]->tk.attribute==UGRET_EQL){
                    temp_code(n->child[0]);
                    temp_code(n->child[1]->child[1]);
                    if(lable_table[lab_index-2]!=NULL){
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=SUB;
                        q_table[q_index].re=temp_table[temp_index-2].name;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2="#1";
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2=temp_table[temp_index-1].name;
                        temp_index-=2;
                        q_table[q_index].op=BGE;
                        q_table[q_index++].args1=lable_table[lab_index-2];
                    }
                    else{
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index++].args2=temp_table[temp_index-2].name;
                        q_table[q_index].op=BLE;
                        q_table[q_index++].args1=lable_table[lab_index-1];
                    }
                }
                if(n->child[1]->child[0]->tk.attribute==GRET_EQL){
                    temp_code(n->child[0]);
                    temp_code(n->child[1]->child[1]);
                    if(lable_table[lab_index-2]!=NULL){
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=ADD;
                        q_table[q_index].re=temp_table[temp_index-2].name;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2="#1";
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index++].args2=temp_table[temp_index-1].name;
                        temp_index-=2;
                        q_table[q_index].op=BGE;
                        q_table[q_index++].args1=lable_table[lab_index-2];
                    }
                    else{
                        if(temp_table[temp_index-2].name[0]!='r'){
                            char* a=get_temp_name();
                            q_table[q_index].op=MOV;
                            q_table[q_index].args1=temp_table[temp_index-2].name;
                            q_table[q_index++].re=a;
                            temp_table[temp_index-2].name=a;
                        }
                        q_table[q_index].op=CMP;
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index++].args2=temp_table[temp_index-2].name;
                        q_table[q_index].op=BGE;
                        q_table[q_index++].args1=lable_table[lab_index-1];
                        temp_index-=2;
                    }
                }
                break;
            case RELEXP1:
                printf("RELEXP1");
                break;
            case FUNCRPREFIX:
                if(!n->child[1]->empty) temp_code(n->child[1]);
                break;
            case VAR_DECL:
                temp_code(n->child[1]);
                break;
            case CONST_DECL:
                {
                    int i;
                    if((i=find_id(n->child[2]->tk.id->data,n->child[2]->tk.id->data_size))==-1||(id_table[i].block_level!=block_level)){
                        if(block_level==0){
                        id_table[id_index].name=n->child[2]->tk.id->data;
                        id_table[id_index].name_size=n->child[2]->tk.id->data_size;
                        id_table[id_index].isconst=0;
                        id_table[id_index].isglob=1;
                        id_table[id_index].block_level=block_level;
                        id_table[id_index].value="#0";
                        temp_index--;
                        if(!n->child[4]->empty) {
                            temp_code(n->child[4]);
                            if(temp_table[temp_index-1].name[0]=='r'){
                                printf("invaild initial value\n");
                                return;
                            }
                            id_table[id_index].value=temp_table[temp_index-1].name;
                        }
                        else{
                            printf("erro const value not have initial value\n");
                        }
                        id_index++;
                        if(n->child[5]->child[0]->tk.type!=END) temp_code(n->child[5]);
                        return;
                    }
                        q_table[q_index].re="sp";
                        q_table[q_index].args1="sp";
                        q_table[q_index].args2="#4";
                        q_table[q_index++].op=SUB;
                        id_table[id_index].name=n->child[2]->tk.id->data;
                        id_table[id_index].name_size=n->child[2]->tk.id->data_size;
                        id_table[id_index].stack_index=stack_len;
                        id_table[id_index].isconst=1;
                        id_table[id_index++].block_level=block_level;
                        stack_len++;
                        temp_code(n->child[4]);
                        if(temp_table[temp_index-1].name[0]!='r'){
                            q_table[q_index].re=get_temp_name();
                            q_table[q_index].args1=temp_table[temp_index-1].name;
                            temp_table[temp_index-1].name=q_table[q_index].re;
                            q_table[q_index++].op=MOV;      
                        }
                        char* a=(char*)malloc(sizeof(char)*10);
                        memset(a,0,sizeof(char)*10);
                        sprintf(a,"[sp, #%d]",(stack_len-id_table[id_index-1].stack_index-1)*4);
                        q_table[q_index].re=a;
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index++].op=STR;
                        temp_index--;
                        if(n->child[5]->child[0]->tk.type!=END){
                            temp_code(n->child[5]);
                        }
                    }
                    else{
                        printf("erro the const value %s has already defined\n",n->child[2]->tk.id->data);
                    }
                }
                
                break;
            case CONSTPREFIX:
                {
                    int i;
                    if((i=find_id(n->child[1]->tk.id->data,n->child[1]->tk.id->data_size))==-1||(id_table[i].block_level!=block_level)){
                        if(block_level==0){
                        id_table[id_index].name=n->child[1]->tk.id->data;
                        id_table[id_index].name_size=n->child[1]->tk.id->data_size;
                        id_table[id_index].isconst=0;
                        id_table[id_index].isglob=1;
                        id_table[id_index].block_level=block_level;
                        id_table[id_index].value="#0";
                        temp_index--;
                        if(!n->child[3]->empty) {
                            temp_code(n->child[3]);
                            if(temp_table[temp_index-1].name[0]=='r'){
                                printf("invaild initial value\n");
                                return;
                            }
                            id_table[id_index].value=temp_table[temp_index-1].name;
                        }
                        else{
                            printf("erro const value not have initial value\n");
                        }
                        id_index++;
                        if(!n->child[4]->empty) temp_code(n->child[4]);
                        return;
                    }
                        q_table[q_index].re="sp";
                        q_table[q_index].args1="sp";
                        q_table[q_index].args2="#4";
                        q_table[q_index++].op=SUB;
                        id_table[id_index].name=n->child[1]->tk.id->data;
                        id_table[id_index].name_size=n->child[1]->tk.id->data_size;
                        id_table[id_index].stack_index=stack_len;
                        id_table[id_index].isconst=1;
                        id_table[id_index++].block_level=block_level;
                        stack_len++;
                        temp_code(n->child[3]);
                        if(temp_table[temp_index-1].name[0]!='r'){
                            q_table[q_index].re=get_temp_name();
                            q_table[q_index].args1=temp_table[temp_index-1].name;
                            temp_table[temp_index-1].name=q_table[q_index].re;
                            q_table[q_index++].op=MOV;      
                        }
                        char* a=(char*)malloc(sizeof(char)*10);
                        memset(a,0,sizeof(char)*10);
                        sprintf(a,"[sp, #%d]",(stack_len-id_table[id_index-1].stack_index-1)*4);
                        q_table[q_index].re=a;
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index++].op=STR;
                        temp_index--;
                        if(n->child[5]->child[0]->tk.type!=END){
                            temp_code(n->child[5]);
                        }
                    }
                    else{
                        printf("erro the const value %s has already defined\n",n->child[1]->tk.id->data);
                    }
                }
                break;
            case DATADECLPREFIX:
                temp_code(n->child[1]);
                break;
            case DATADECL:
                temp_code(n->child[0]);
                break;
            case IDARRY:
                {
                    int i;
                if((i=find_id(n->child[0]->tk.id->data,n->child[0]->tk.id->data_size))==-1||(id_table[i].block_level!=block_level)){
                    if(block_level==0){
                        id_table[id_index].name=n->child[0]->tk.id->data;
                        id_table[id_index].name_size=n->child[0]->tk.id->data_size;
                        id_table[id_index].isconst=0;
                        id_table[id_index].isglob=1;
                        id_table[id_index].block_level=block_level;
                        id_table[id_index].value="#0";
                        temp_index--;
                        if(!n->child[1]->empty) {
                            temp_code(n->child[1]);
                            if(temp_table[temp_index-1].name[0]=='r'){
                                printf("invaild initial value\n");
                                return;
                            }
                            id_table[id_index].value=temp_table[temp_index-1].name;
                        }
                        id_index++;
                        if(!n->child[2]->empty) temp_code(n->child[2]);
                        return;
                    }
                    id_table[id_index].name=n->child[0]->tk.id->data;
                    id_table[id_index].name_size=n->child[0]->tk.id->data_size;
                    id_table[id_index].stack_index=stack_len;
                    id_table[id_index].isconst=0;
                    id_table[id_index++].block_level=block_level;
                    q_table[q_index].args2="#4";
                    q_table[q_index].args1="sp";
                    q_table[q_index].re="sp";
                    q_table[q_index++].op=SUB;
                    stack_len++;
                    if(n->child[1]->empty){
                        char* a=(char*)malloc(sizeof(char)*10);
                        char* ta=get_temp_name();
                        q_table[q_index].args1="#0";
                        q_table[q_index].re=ta;
                        q_table[q_index++].op=MOV;
                        memset(a,0,sizeof(char)*10);
                        sprintf(a,"[sp, #%d]",(stack_len-id_table[id_index-1].stack_index-1)*4);
                        q_table[q_index].args1=ta;
                        q_table[q_index].re=a;
                        q_table[q_index++].op=STR;
                    }
                    if(!n->child[1]->empty){
                        temp_code(n->child[1]);
                        if(temp_table[temp_index-1].name[0]!='r'){
                            q_table[q_index].re=get_temp_name();
                            q_table[q_index].args1=temp_table[temp_index-1].name;
                            temp_table[temp_index-1].name=q_table[q_index].re;
                            q_table[q_index++].op=MOV;      
                        }
                        char* a=(char*)malloc(sizeof(char)*10);
                        memset(a,0,sizeof(char)*10);
                        sprintf(a,"[sp, #%d]",(stack_len-id_table[id_index-1].stack_index-1)*4);
                        q_table[q_index].re=a;
                        q_table[q_index].args1=temp_table[temp_index-1].name;
                        q_table[q_index++].op=STR;
                        temp_index--;
                    }
                }
                else{
                    printf("erro the var %s has already defined\n",n->child[0]->tk.id->data);
                }
                }
                if(!n->child[2]->empty) temp_code(n->child[2]);
                break;
            case IDARRYPREFIX:
                temp_code(n->child[1]);
                break;
            case DECL:
                num_of_para=0;
                if(n->index==6){
                    int t_len=stack_len;
                    if(find_func(n->child[1]->tk.id->data,n->child[1]->tk.id->data_size)==-1){
                        func_table[func_index].name=n->child[1]->tk.id->data;
                        func_table[func_index].name_size=n->child[1]->tk.id->data_size;
                        func_table[func_index++].ret_type=VOID;   
                    }
                    if(!n->child[3]->empty){
                        if(n->child[5]->child[0]->tk.type!=END) {
                            temp_code(n->child[3]);   
                            int t_stack_index=id_index;
                            q_table[q_index].args1=n->child[1]->tk.id->data;
                            q_table[q_index++].op=FUNC;
                            q_table[q_index].args1="lr";
                            q_table[q_index++].op=PUSH;
                            ret_link[ret_index++]=stack_len;
                            stack_len++;
                            int temp_t=temp_index;
                            temp_code(n->child[5]);
                            id_index=t_stack_index;
                            temp_index=temp_t;
                            ret_index--;
                        }  
                    }
                    if(n->child[3]->empty){
                        if(n->child[5]->child[0]->tk.type!=END) {
                            int t_stack_index=id_index;
                            q_table[q_index].args1=n->child[1]->tk.id->data;
                            q_table[q_index++].op=FUNC;
                            q_table[q_index].args1="lr";
                            q_table[q_index++].op=PUSH;
                            ret_link[ret_index++]=stack_len;
                            stack_len++;
                            int temp_t=temp_index;
                            temp_code(n->child[5]);
                            id_index=t_stack_index;
                            temp_index=temp_t;
                            ret_index--;
                        }  
                    }
                    stack_len=t_len;    
                }
                if(n->index==2){
                    temp_code(n->child[1]);
                }
                if(n->index==1){
                    temp_code(n->child[0]);
                }
                break;
            case PARA:
                if(!n->child[2]->empty){
                    num_of_para++;
                    id_table[id_index].name=n->child[1]->tk.id->data;
                    id_table[id_index].name_size=n->child[1]->tk.id->data_size;
                    id_table[id_index].stack_index=stack_len++;
                    id_table[id_index].isconst=0;
                    id_table[id_index++].block_level=block_level+1;
                    temp_code(n->child[2]);
                }
                if(n->child[2]->empty){
                    num_of_para++;
                    id_table[id_index].name=n->child[1]->tk.id->data;
                    id_table[id_index].name_size=n->child[1]->tk.id->data_size;
                    id_table[id_index].stack_index=stack_len++;
                    id_table[id_index].isconst=0;
                    id_table[id_index++].block_level=block_level+1;
                }
                break;
            case DECLPREFIX:
                if(n->child[1]->child[0]->tk.type==LPARES){
                    int t_len=stack_len;
                    func_table[func_index].name=n->child[0]->tk.id->data;
                    func_table[func_index].ret_type=INT;
                    func_table[func_index++].name_size=n->child[0]->tk.id->data_size;
                    int t_stack_index=id_index;
                    if(!n->child[1]->child[1]->empty&&n->child[1]->child[3]->child[0]->tk.type!=END) temp_code(n->child[1]->child[1]);
                    if(n->child[1]->child[3]->child[0]->tk.type!=END){
                        q_table[q_index].args1=n->child[0]->tk.id->data;
                        q_table[q_index++].op=FUNC;
                        q_table[q_index].args1="lr";
                        q_table[q_index++].op=PUSH;
                        ret_link[ret_index++]=stack_len;
                        stack_len++;
                        int temp_t=temp_index;
                        temp_code(n->child[1]->child[3]);
                        temp_index=temp_t;
                        id_index=t_stack_index; 
                        stack_len=t_len;
                        ret_index--;
                    }
                    
                }
                if(n->child[1]->child[0]->tk.type==END){    
                    int i;
                    if((i=find_id(n->child[0]->tk.id->data,n->child[0]->tk.id->data_size)==-1)||(id_table[i].block_level!=block_level)){
                        if(temp_table[temp_index-1].name[0]=='r'){
                            printf("invaild initial value\n");
                            return;
                        }
                        id_table[id_index].name=n->child[0]->tk.id->data;
                        id_table[id_index].name_size=n->child[0]->tk.id->data_size;
                        id_table[id_index].isconst=0;
                        id_table[id_index].isglob=1;
                        id_table[id_index].block_level=block_level;
                        id_table[id_index++].value="#0";
                        temp_index--;
                        if(!n->child[1]->child[2]->empty) temp_code(n->child[1]->child[2]);
                    }
                    else{
                        printf("erro the var %s has already defined\n",n->child[0]->tk.id->data);
                    }
                }
                if(n->child[1]->child[0]->tk.type==COMMA){
                    temp_code(n->child[1]);
                }
                if(n->child[1]->child[0]->tk.attribute==ASSIGN){
                    int i;
                    if((i=find_id(n->child[0]->tk.id->data,n->child[0]->tk.id->data_size)==-1)||(id_table[i].block_level!=block_level)){
                        temp_code(n->child[1]->child[1]);
                        if(temp_table[temp_index-1].name[0]=='r'){
                            printf("invaild initial value\n");
                            return;
                        }
                        id_table[id_index].name=n->child[0]->tk.id->data;
                        id_table[id_index].name_size=n->child[0]->tk.id->data_size;
                        id_table[id_index].isconst=0;
                        id_table[id_index].isglob=1;
                        id_table[id_index].block_level=block_level;
                        id_table[id_index++].value=temp_table[temp_index-1].name;
                        temp_index--;
                        if(!n->child[1]->child[2]->empty) temp_code(n->child[1]->child[2]);
                    }
                    else{
                        printf("erro the var %s has already defined\n",n->child[0]->tk.id->data);
                    }
                }
                break;
            case DECLPREPREFIX:
                printf("DECLPREPREFIX");
                break;
            case PARAPREFIX:
                temp_code(n->child[1]);
                break;
            case STMT:
                if(n->child[0]->type==EXP){
                    temp_code(n->child[0]);
                    temp_index--;
                    break;
                }
                if(n->child[0]->tk.type==BREAK){
                    if(lab_index!=0&&lab_index-is_if-2>-1){
                        q_table[q_index].args1=lable_table[lab_index-is_if-2];
                        q_table[q_index++].op=JMP;
                    }
                    break;
                }
                if(n->child[0]->tk.type==CONTINUE){
                    if(lab_index!=0&&lab_index-is_if-3>-1){
                        q_table[q_index].args1=lable_table[lab_index-is_if-3];
                        q_table[q_index++].op=JMP;
                    }
                    break;
                }
                if(n->child[0]->type==BLOCK){
                    temp_code(n->child[0]);
                    break;
                }
                if(n->child[0]->tk.type==ID&&n->child[1]->tk.attribute==ASSIGN){
                    temp_code(n->child[2]);
                    int t_temp=temp_index;
                    if(temp_table[temp_index-1].name[0]!='r'){
                        temp_table[temp_index++].name=get_temp_name();
                        q_table[q_index].args1=temp_table[temp_index-2].name;
                        q_table[q_index].re=temp_table[temp_index-1].name;
                        q_table[q_index++].op=MOV;
                    }
                    int i;
                    if((i=find_id(n->child[0]->tk.id->data,n->child[0]->tk.id->data_size))!=-1&&!id_table[i].isconst){
                        if(id_table[i].isglob){
                            q_table[q_index].args1=temp_table[temp_index-1].name;
                            q_table[q_index].re=n->child[0]->tk.id->data;
                            q_table[q_index++].op=STR;
                        }
                        else{
                            q_table[q_index].args1=temp_table[temp_index-1].name;
                            q_table[q_index].op=STR;
                            temp_index=t_temp;
                            char* a=(char*)malloc(sizeof(char)*10);
                            memset(a,0,sizeof(char)*10);
                            sprintf(a,"[sp, #%d]",(stack_len-id_table[i].stack_index-1)*4);
                            q_table[q_index++].re=a;
                        } 
                    }
                    else{
                        printf("erro the var %s not defined or the var is const\n",n->child[0]->tk.id->data);
                    }
                    temp_index--;
                    break;
                }
                if(n->child[0]&&n->child[1]) 
                if(n->child[0]->tk.type==RET&&n->child[1]->tk.type==END){
                    q_table[q_index].op=ADD;
                    char* a=(char*)malloc(sizeof(char)*10);
                    memset(a,0,sizeof(char)*10);
                    sprintf(a,"#%d",(stack_len-ret_link[ret_index-1]-1)*4);
                    q_table[q_index].args2=a;
                    q_table[q_index].args1="sp";
                    q_table[q_index++].re="sp";
                    q_table[q_index].op=POP;
                    q_table[q_index++].re="pc";
                }
                if(n->child[0]->tk.type==RET&&n->child[1]->tk.type!=END){
                    temp_code(n->child[1]);
                    q_table[q_index].op=ADD;
                    char* a=(char*)malloc(sizeof(char)*10);
                    memset(a,0,sizeof(char)*10);
                    //printf("%d %d\n",stack_len,ret_link[ret_index-1]);
                    sprintf(a,"#%d",(stack_len-ret_link[ret_index-1]-1)*4);
                    q_table[q_index].args2=a;
                    q_table[q_index].args1="sp";
                    q_table[q_index++].re="sp";
                    temp_table[temp_index].name=get_temp_name();
                    q_table[q_index].op=POP;
                    q_table[q_index++].re=temp_table[temp_index++].name;
                    if(temp_table[temp_index-2].name[0]!='r'){
                        q_table[q_index].re=get_temp_name();
                        q_table[q_index].op=MOV;
                        q_table[q_index++].args1=temp_table[temp_index-2].name;
                        q_table[q_index].op=PUSH;
                        q_table[q_index].args1=q_table[q_index-1].re;
                        q_index++;
                    }
                    else {
                        q_table[q_index].op=PUSH;
                        q_table[q_index++].args1=temp_table[temp_index-2].name;
                    }
                    q_table[q_index].re="pc";
                    q_table[q_index].op=MOV;
                    q_table[q_index].args1=temp_table[temp_index-1].name;
                    q_index++;
                    temp_index-=2;
                }
                if(n->child[0]->tk.type==IF){
                    int tif=is_if;
                    int li=lab_index;
                    is_if+=2;
                    char* c;
                    if(!n->child[5]->empty){
                        c=get_lab_name();
                        is_if+=1;
                    }
                    char* a=get_lab_name();
                    char* b=get_lab_name();
                    temp_code(n->child[2]);
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=b;
                    temp_code(n->child[4]);
                    if(!n->child[5]->empty){
                        q_table[q_index].op=JMP;
                        q_table[q_index++].args1=c;
                    }
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=a;
                    if(!n->child[5]->empty){ 
                        temp_code(n->child[5]->child[1]);
                        q_table[q_index].op=LABLE;
                        q_table[q_index++].args1=c;
                    }
                    lab_index=li;
                    is_if=tif;
                }
                if(n->child[0]->tk.type==WHILE){
                    char* c=get_lab_name();
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=c;
                    char* a=get_lab_name();
                    char* b=get_lab_name();
                    temp_code(n->child[2]);
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=b;
                    temp_code(n->child[4]);
                    q_table[q_index].op=JMP;
                    q_table[q_index++].args1=c;
                    q_table[q_index].op=LABLE;
                    q_table[q_index++].args1=a; 
                    lab_index-=3;
                }
                break;
            case BLOCK:
                block_level++;
                if(!n->child[1]->empty){
                    int id_stack_top=id_index;
                    temp_code(n->child[1]);
                    id_index=id_stack_top;
                }
                block_level--;
                break;
            case BLOCKITEM:
                
                if(n->child[0]->type==DATADECL){
                    temp_code(n->child[0]);
                    if(!n->child[1]->empty) temp_code(n->child[1]);
                }
                if(n->child[0]->type==STMT){
                    temp_code(n->child[0]);
                    if(!n->child[1]->empty) temp_code(n->child[1]);
                }
                break;
            case IFPREFIX:
                printf("IFPREFIX");
                break;
            case DECLPREPREPREFIX:
                if(n->child[0]->type==BLOCK){
                    temp_code(n->child[0]);
                }
                break;
            case VOIDDECLPREFIX:
                if(n->child[0]->type!=TOKEN){
                    temp_code(n->child[0]);
                }
                break;
            case COMUNIT:
                if(!n->empty){
                    temp_code(n->child[0]);
                    if(!n->child[1]->empty) temp_code(n->child[1]);
                    break;
                }
                break;
        }
    }
}