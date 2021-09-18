#include "hs.h"

#define BUFSIZE 10000
#define INT 320
#define BREAK 321
#define CONTINUE 322
#define WHILE 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define EQL 6
#define UEQL 7
#define GRET 8
#define UGRET 9
#define GRET_EQL 10
#define UGRET_EQL 11
#define NOT 12
#define AND 13
#define OR 14
#define ID 15
#define IF 16
#define ELSE 17
#define RBRACE 18 // }
#define LBRACE 19 // {
#define RPARES 20 // )
#define LPARES 21 // (
#define ASSIGN 22
#define NUMBER 23
#define END 24
#define MOD 25
#define RELOP 26
#define OP 28
#define CONST 27
#define VOID 29
#define COMMA 30
#define RET 31

#define TOKEN 199
#define EXP 200
#define ADDEXP 201
#define MULEXP 202
#define ADDEXP1 203
#define MULEXP1 204
#define UNARYEXP 205
#define PRIMEXP 206
#define FUNCRPARAM 207
#define IDPREFIX 208
#define COND 209
#define LOREXP 210
#define LANDEXP 211
#define RELEXP 213
#define LOREXP1 214
#define LANDEXP1 215
#define CONSTPREFIX 216
#define RELEXP1 217
#define FUNCRPREFIX 218
#define VAR_DECL 219
#define CONST_DECL 220
#define DATADECLPREFIX 221
#define DATADECL 222
#define IDARRY 223
#define IDARRYPREFIX 224
#define DECL 225
#define PARA 226
#define DECLPREFIX 227
#define DECLPREPREFIX 228
#define PARAPREFIX 229
#define STMT 230
#define BLOCK 231
#define BLOCKITEM 232
#define IFPREFIX 233
#define DECLPREPREPREFIX 234
#define COMUNIT 235

#define FUNC 236
#define VAR 237
#define CONSTNUMVER 238
#define VOIDDECLPREFIX 239
#define CMP 240
#define TEQ 241
#define BEQ 242
#define BNE 243
#define BGE 244
#define BLE 245
#define STR 246
typedef struct token
{
    /* data */
    int type;
    int attribute;
    node* id;
    node* number;
}token;
void print_token(token tk);

typedef struct sync_node
{
    /* data */
    token tk;
    int index;
    struct sync_node* child[100];
    int type;
    bool empty;
}sync_node;
typedef struct linknode
{
    /* data */
    sync_node* node;
    struct linknode* next;
    struct linknode* pre;

}linknode;
void print_type(linknode* n){
    switch(n->node->type){
        case EXP:
            printf("EXP");
            break;
        case ADDEXP:
            printf("ADDEXP");
            break;
        case MULEXP:
            printf("MULEXP");
            break;
        case ADDEXP1:
            printf("ADDEXP1");
            break;
        case MULEXP1:
            printf("MULEXP1");
            break;
        case UNARYEXP:
            printf("UNARYEXP");
            break;
        case PRIMEXP:
            printf("PRIMEXP");
            break;
        case FUNCRPARAM:
            printf("FUNCRPARAM");
            break;
        case IDPREFIX:
            printf("IDPREFIX");
            break;
        case COND:
            printf("COND");
            break;
        case LOREXP:
            printf("LOREXP");
            break;
        case LOREXP1:
            printf("LOREXP1");
            break;
        case LANDEXP:
            printf("LANDEXP");
            break;
        case RELEXP:
            printf("RELEXP");
            break;
        case LANDEXP1:
            printf("LANDEXP1");
            break;
        case RELEXP1:
            printf("RELEXP1");
            break;
        case FUNCRPREFIX:
            printf("FUNCRPREFIX");
            break;
        case TOKEN:
            printf("TOKEN");
            print_token(n->node->tk);
            break;
        case VAR_DECL:
            printf("VAR_DECL");
            break;
        case CONST_DECL:
            printf("CONST_DECL");
            break;
        case DATADECLPREFIX:
            printf("DATADECLPREFIX");
            break;
        case DATADECL:
            printf("DATADECL");
            break;
        case IDARRY:
            printf("IDARRY");
            break;
        case IDARRYPREFIX:
            printf("IDARRYPREFIX");
            break;
        case DECL:
            printf("DECL");
            break;
        case PARA:
            printf("PARA");
            break;
        case DECLPREFIX:
            printf("DECLPREFIX");
            break;
        case DECLPREPREFIX:
            printf("DECLPREPREFIX");
            break;
        case PARAPREFIX:
            printf("PARAPREFIX");
            break;
        case STMT:
            printf("STMT");
            break;
        case BLOCK:
            printf("BLOCK");
            break;
        case BLOCKITEM:
            printf("BLOCKITEM");
            break;
        case IFPREFIX:
            printf("IFPREFIX");
            break;
        case DECLPREPREPREFIX:
            printf("DECLPREPREPREFIX");
            break;
        case COMUNIT:
            printf("COMUIT");
            break;
        case VOIDDECLPREFIX:
            printf("VOIDDECLPREFIX");
            break;
        case CONSTPREFIX:
            printf("CONSTPREFIX");
            break;
    }
}
typedef struct sync_link
{
    /* data */
    linknode* tail;
    int num;

}sync_linktable;

void sync_link_init(sync_linktable* l){
    l->num=0;
    l->tail=(linknode*)malloc(sizeof(linknode));
}
linknode* push(sync_linktable* l,sync_node* sync_n){
    linknode* t=(linknode*)malloc(sizeof(linknode));
    memset(t,0,sizeof(linknode));
    t->node=sync_n;
    linknode* n=l->tail->next;
    t->pre=l->tail;
    t->next=n;
    l->tail->next=t;
    l->tail=t;
    l->num++;
    return t;
}
linknode* pop(sync_linktable* l){
    l->num--;
    linknode* n=l->tail;
    l->tail=l->tail->pre;
    return n;
}
linknode* top(sync_linktable* l){
    return l->tail;
}
bool is_empty(sync_linktable* l){
    return l->num==0;
}

void p_resv(sync_node* n,int blank,bool print){
    if(n==NULL||n->empty==1) return;
    else{
        int i;
        if(print){
            char* a=(char*)malloc((blank+1)*sizeof(char));
            memset(a,'-',blank*sizeof(char));
            a[blank]=0;
            linknode ln;
            ln.node=n;
            printf("%s",a);
            print_type(&ln);
            printf("\n");
        }
        int index=0;
        for(i=0;i<100;i++){
            if(n->child[i]!=NULL) index++;
            else break;
        }
        int j;
        for(j=0,i=index-1;j<index&&j<i&&i>-1;j++,i--){
            sync_node* t=n->child[i];
            n->child[i]=n->child[j];
            n->child[j]=t;
        }
        for(j=0;j<index;j++){
           p_resv(n->child[j],blank+1,print);
        }
    }
}
void p(sync_node* n,int blank){
    if(n==NULL||n->empty==1) return;
    else{
        int i;
        char* a=(char*)malloc((blank+1)*sizeof(char));
        memset(a,'-',blank*sizeof(char));
        a[blank]=0;
        linknode ln;
        ln.node=n;
        printf("%s",a);
        print_type(&ln);
        printf("\n");
        int index=0;
        for(i=0;i<100;i++){
            if(n->child[i]!=NULL) p(n->child[i],blank+1);
            else break;
        }
    }
}

void p_child(sync_node* n){
    int i=0;
    while(n->child[i]!=NULL){
        printf("%p ",n->child[i]);
        i++;
    }
    printf("\n");
}

hstable id_hs;
hstable number_hs;
char *start;
char* s;
token t_arry[BUFSIZE];
int t_index=0;
int curr_line=1;
char* get_tokenobj(token tk){
    if(tk.id!=NULL)
    return tk.id->data;
    return NULL;
}
char* get_tokenobjnumber(token tk){
    if(tk.number!=NULL)
    return tk.number->data;
    return NULL;
}

char* raise_erro(char* start,char* curr_erro){
    char erro[1000];
    char* ptr_erro=erro;
    while(start!=s-1&&*start!=13){
        *start--;
    }
    start++;
    while(*start!=13&&*start!='\0'){
        *ptr_erro++=*start++;
    }
    *ptr_erro='\0';
    printf("syntax erro :%s in line %d! line %d:\"%s\"\n",curr_erro,curr_line,curr_line,erro);
    return start;
}
void print_token(token tk){
    switch(tk.type){
        case INT:
            printf("<%s %d - >","int",tk.type);
            break;
        case WHILE:
            printf("<%s %d - >","while",tk.type);
            break;
        case ID:
            printf("<%s %d %s >","id",tk.type,get_tokenobj(tk));
            break;
        case IF:
            printf("<%s %d - >","if",tk.type);
            break;
        case ELSE:
            printf("<%s %d - >","else",tk.type);
            break;
        case RBRACE:
            printf("<%s %d - >","}",tk.type);
            break;
        case LBRACE:
            printf("<%s %d - >","{",tk.type);
            break;
        case RPARES:
            printf("<%s %d - >",")",tk.type);
            break;
        case LPARES:
            printf("<%s %d - >","(",tk.type);
            break;
        case NUMBER:
            printf("<%s %d %s >","number",tk.type,get_tokenobjnumber(tk));
            break;
        case END:
            printf("<%s %d - >",";",tk.type);
            break;
        case CONST:
            printf("<%s %d - >","const",tk.type);
            break;
        case RET:
            printf("<%s %d - >","return",tk.type);
            break;
        case VOID:
            printf("<%s %d - >","void",tk.type);
            break;
        case COMMA:
            printf("<%s %d - >",",",tk.type);
            break;
        case BREAK:
            printf("<%s %d - >","break",tk.type);
            break;
        case CONTINUE:
            printf("<%s %d - >","continue",tk.type);
            break;
        case RELOP:
            switch (tk.attribute)
            {
                case EQL:
                    printf("<%s %s %d >","==","relop",tk.attribute);
                    break;
                case UEQL:
                    printf("<%s %s %d >","!=","relop",tk.attribute);
                    break;
                case GRET:
                    printf("<%s %s %d >",">","relop",tk.attribute);
                    break;
                case UGRET:
                    printf("<%s %s %d >","<","relop",tk.attribute);
                    break;
                case GRET_EQL:
                    printf("<%s %s %d >",">=","relop",tk.attribute);
                    break;
                case UGRET_EQL:
                    printf("<%s %s %d >","<=","relop",tk.attribute);
                    break;
                case NOT:
                    printf("<%s %s %d >","!","relop",tk.attribute);
                    break;
                case AND:
                    printf("<%s %s %d >","&&","relop",tk.attribute);
                    break;
                case OR:
                    printf("<%s %s %d >","||","relop",tk.attribute);
                    break;  
            }
        case OP:{
            switch(tk.attribute)
            {
                case ADD:
                    printf("<%s %s %d >","+","op",tk.attribute);
                    break;
                case SUB:
                    printf("<%s %s %d >","-","op",tk.attribute);
                    break;
                case MUL:
                    printf("<%s %s %d >","*","op",tk.attribute);
                    break;
                case DIV:
                    printf("<%s %s %d >","/","op",tk.attribute);
                    break;
                case ASSIGN:
                    printf("<%s %s %d >","=","op",tk.attribute);
                    break;
                case MOD:
                    printf("<%s %s %d >","%","op",tk.attribute);
                    break;
            }
        }
    }
}