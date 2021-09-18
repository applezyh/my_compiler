#include "struct.h"

bool spot_int(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '){
        switch(*start){
            case 'i':
                if(state==0){state=1;break;}
                else return 0;
            case 'n':
                if(state==1){state=2;break;}
                else return 0;
            case 't':
                if(state==2) {state=3;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==3;
}

bool spot_void(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!='{'){
        switch(*start){
            case 'v':
                if(state==0){state=1;break;}
                else return 0;
            case 'o':
                if(state==1){state=2;break;}
                else return 0;
            case 'i':
                if(state==2) {state=3;break;}
                else return 0;
            case 'd':
                if(state==3) {state=4;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==4;
}

bool spot_while(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!='('){
        switch(*start){
            case 'w':
                if(state==0){state=1;break;}
                else return 0;
            case 'h':
                if(state==1){state=2;break;}
                else return 0;
            case 'i':
                if(state==2) {state=3;break;}
                else return 0;
            case 'l':
                if(state==3) {state=4;break;}
                else return 0;
            case 'e':
                if(state==4) {state=5;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==5;
}

bool spot_break(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!=';'){
        switch(*start){
            case 'b':
                if(state==0){state=1;break;}
                else return 0;
            case 'r':
                if(state==1){state=2;break;}
                else return 0;
            case 'e':
                if(state==2) {state=3;break;}
                else return 0;
            case 'a':
                if(state==3) {state=4;break;}
                else return 0;
            case 'k':
                if(state==4) {state=5;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==5;
}

bool spot_return(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!='('&&*start!=';'){
        switch(*start){
            case 'r':
                if(state==0){state=1;break;}
                if(state==4){state=5;break;}
                else return 0;
            case 'e':
                if(state==1){state=2;break;}
                else return 0;
            case 't':
                if(state==2) {state=3;break;}
                else return 0;
            case 'u':
                if(state==3) {state=4;break;}
                else return 0;
            case 'n':
                if(state==5) {state=6;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==6;
}

bool spot_continue(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!=';'){
        switch(*start){
            case 'c':
                if(state==0){state=1;break;}
                else return 0;
            case 'o':
                if(state==1){state=2;break;}
                else return 0;
            case 'n':
                if(state==2) {state=3;break;}
                if(state==5) {state=6;break;}
                else return 0;
            case 't':
                if(state==3) {state=4;break;}
                else return 0;
            case 'i':
                if(state==4) {state=5;break;}
                else return 0;
            case 'u':
                if(state==6) {state=7;break;}
                else return 0;
            case 'e':
                if(state==7) {state=8;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==8;
}

bool spot_const(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '){
        switch(*start){
            case 'c':
                if(state==0){state=1;break;}
                else return 0;
            case 'o':
                if(state==1){state=2;break;}
                else return 0;
            case 'n':
                if(state==2) {state=3;break;}
                else return 0;
            case 's':
                if(state==3) {state=4;break;}
                else return 0;
            case 't':
                if(state==4) {state=5;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==5;
}

bool spot_if(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!='('){
        switch(*start){
            case 'i':
                if(state==0){state=1;break;}
                else return 0;
            case 'f':
                if(state==1){state=2;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==2;
}

bool spot_else(char *start){
    int state=0;
    while(*start!='\0'&&*start!=' '&&*start!='{'&&*start!=13){
        switch(*start){
            case 'e':
                if(state==0){state=1;break;}
                if(state==3) {state=4;break;}
                else return 0;
            case 'l':
                if(state==1){state=2;break;}
                else return 0;
            case 's':
                if(state==2) {state=3;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    return state==4;
}

bool spot_id(char *start,int* size){
    int state=0;
    int id_size=0;
    while(('A'<=*start&&*start<='Z')||('a'<=*start&&*start<='z')||('0'<=*start&&*start<='9')||*start=='_'){
        int ca;
        if(('A'<=*start&&*start<='Z')||('a'<=*start&&*start<='z')||*start=='_') ca=0;
        else ca=1;
        switch(ca){
            case 0:
                if(state==0){state=1;id_size++;break;}
                if(state==1){state=1;id_size++;break;}
                if(state==2){state=1;id_size++;break;}
                else return 0;
            case 1:
                if(state==0) return 0;
                if(state==1){state=2;id_size++;break;}
                if(state==2){state=2;id_size++;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    *size=id_size;
    return state==2||state==1;
}

bool spot_number(char *start,int* size){
    int state=0;
    int number_size=0;
    while('0'<=*start&&*start<='9'){
        int ca;
        if(*start=='0') ca=0;
        else ca=1;
        switch(ca){
            case 0:
                if(state==0){number_size++;if(*(start+1)<'0'||*(start+1)>'9'){*size=number_size;return 1;} return 0;}
                if(state==1){state=1;number_size++;break;}
                else return 0;
            case 1:
                if(state==0){state=1;number_size++;break;}
                if(state==1){state=1;number_size++;break;}
                else return 0;
            default:
                return 0;
        }
        start++;
    }
    *size=number_size;
    return state==1;
}


token next(char* start,char** end,sync_node* node){
    token tk;
    while(*start==' '||*start==13){if(*start==13){curr_line++;}start++;*end=start;}
    if(*start=='\0'){
        //printf("end of code\n");
        tk.attribute=-1;
        return tk;
    }
    node->type=TOKEN;
    int id_size=0;
    int number_size=0;
    if(spot_while(start)){start+=5;tk.type=WHILE;node->tk=tk;*end=start;return tk;}
    if(spot_const(start)){start+=5;tk.type=CONST;node->tk=tk;*end=start;return tk;}
    if(spot_break(start)){start+=5;tk.type=BREAK;node->tk=tk;*end=start;return tk;}
    if(spot_continue(start)){start+=8;tk.type=CONTINUE;node->tk=tk;*end=start;return tk;}
    if(spot_if(start)){start+=2;tk.type=IF;*end=start;node->tk=tk;return tk;}
    if(spot_else(start)){start+=4;tk.type=ELSE;*end=start;node->tk=tk;return tk;}
    if(spot_int(start)){start+=3;tk.type=INT;*end=start;node->tk=tk;return tk;}
    if(spot_void(start)){start+=4;tk.type=VOID;*end=start;node->tk=tk;return tk;}
    if(spot_return(start)){start+=6;tk.type=RET;*end=start;node->tk=tk;return tk;}
    if(spot_id(start,&id_size)){
        tk.id=hs_insert(&id_hs,start,id_size);
        start+=id_size;
        *end=start;
        tk.type=ID;
        node->tk=tk;
        return tk;
    }
    if(spot_number(start,&number_size)){
        tk.number=hs_insert(&number_hs,start,number_size);
        start+=number_size;
        *end=start;
        tk.type=NUMBER;
        node->tk=tk;
        return tk;
    }
    if(*start=='+'){start+=1;tk.attribute=ADD;tk.type=OP;*end=start;node->tk=tk;return tk;}
    if(*start=='-'){start+=1;tk.attribute=SUB;tk.type=OP;*end=start;node->tk=tk;return tk;}
    if(*start=='*'){start+=1;tk.attribute=MUL;tk.type=OP;*end=start;node->tk=tk;return tk;}
    if(*start=='/'){start+=1;tk.attribute=DIV;tk.type=OP;*end=start;node->tk=tk;return tk;}
    if(*start=='%'){start+=1;tk.attribute=MOD;tk.type=OP;*end=start;node->tk=tk;return tk;}
    if(*start=='('){start+=1;tk.type=LPARES;*end=start;node->tk=tk;return tk;}
    if(*start==')'){start+=1;tk.type=RPARES;*end=start;node->tk=tk;return tk;}
    if(*start=='{'){start+=1;tk.type=LBRACE;*end=start;node->tk=tk;return tk;}
    if(*start=='}'){start+=1;tk.type=RBRACE;*end=start;node->tk=tk;return tk;}
    if(*start==','){start+=1;tk.type=COMMA;*end=start;node->tk=tk;return tk;}
    if(*start=='!'&&*(start+1)=='='){start+=2;tk.attribute=UEQL;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='!'){start+=1;tk.attribute=NOT;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start==';'){start+=1;tk.type=END;*end=start;node->tk=tk;return tk;}
    if(*start=='='&&*(start+1)=='='){start+=2;tk.attribute=EQL;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='='){start+=1;tk.attribute=ASSIGN;tk.type=OP;*end=start;node->tk=tk;return tk;}
    if(*start=='<'&&*(start+1)=='='){start+=2;tk.attribute=UGRET_EQL;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='>'&&*(start+1)=='='){start+=2;tk.attribute=GRET_EQL;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='&'&&*(start+1)=='&'){start+=2;tk.attribute=AND;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='|'&&*(start+1)=='|'){start+=2;tk.attribute=OR;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='<'){start+=1;tk.attribute=UGRET;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    if(*start=='>'){start+=1;tk.attribute=GRET;tk.type=RELOP;*end=start;node->tk=tk;return tk;}
    else{
        start=raise_erro(start,"\0");
        while(*start!=' '&&*start!='\0'){if(*start==13){curr_line++;}start++;}
        *end=start;
        tk.attribute=-2;
        return tk;
    }   
}