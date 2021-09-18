#include "lex_analy.h"

sync_node* func_para(char* start,char** end);
sync_node* prim_expr(char* start,char** end);
sync_node* unary_expr(char* start,char** end);
sync_node* mul_expr(char* start,char** end);
sync_node* add_expr(char* start,char** end);
sync_node* mul_expr1(char* start,char** end);
sync_node* add_expr1(char* start,char** end);
sync_node* expr(char* start,char** end);

sync_node* func_para(char* start,char** end){
    char* temp=start;
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* cn4=malloc(sizeof(sync_node));
    sync_node* cn5=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    int index=0;
    if((next(start,&start,cn3).type==LPARES)&&(cn5=expr(start,&start))){
        n->child[index++]=cn3;
        n->child[index++]=cn5;
        char* st=start;
        sync_node* cn1=malloc(sizeof(sync_node));
        sync_node* cn2=malloc(sizeof(sync_node));
        memset(cn1,0,sizeof(sync_node));
        memset(cn2,0,sizeof(sync_node));
        while(next(start,&start,cn1).type==COMMA&&(cn2=expr(start,&start))) {
            st=start;
            n->child[index++]=cn1;
            n->child[index++]=cn2;
            cn1=malloc(sizeof(sync_node));
            cn2=malloc(sizeof(sync_node));
            memset(cn1,0,sizeof(sync_node));
            memset(cn2,0,sizeof(sync_node));
        }
        start=st;
        if(next(start,&start,cn4).type!=RPARES){
            *end=start;
            free(n);
            free(cn3);
            free(cn4);
            free(cn1);
            free(cn2);
            free(cn5);
            return 0;
        }
        n->child[index++]=cn4;
        if(cn1==NULL||cn2==NULL){
            if(cn1!=NULL) {free(cn1);cn1=NULL;}
            if(cn2!=NULL) {free(cn2);cn2=NULL;}
        }
        *end=start;
        return n;
    }
    free(n);
    free(cn3);
    free(cn4);
    free(cn5);
    n=NULL;
    return n;
}
sync_node* prim_expr(char* start,char** end){
    char* temp=start;
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    if(next(start,&start,cn1).type==LPARES&&(cn2=expr(start,&start))&&next(start,&start,cn3).type==RPARES) {*end=start;n->child[index++]=cn1;n->child[index++]=cn2;n->child[index++]=cn3;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    start=temp;
    index=0;
    free(cn2);
    free(cn3);
    cn2=NULL;
    cn3=NULL;
    if(next(start,&start,cn1).type==ID) {*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    start=temp;
    index=0;
    if(next(start,&start,cn1).type==NUMBER) {*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    n=NULL;
    cn1=NULL;
    cn2=NULL;
    cn3=NULL;
    return 0;
}
sync_node* unary_expr(char* start,char** end){
    char* temp=start;
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    int index=0;
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    if(next(start,&start,cn1).type==ID&&(cn2=func_para(start,&start))) {*end=start;n->child[index++]=cn1;n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    index=0;
    start=temp;
    if((cn1=prim_expr(start,&start))) {*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    start=temp;
    index=0;
    int t=next(start,&start,cn1).attribute;
    if((t==ADD||t==SUB||t==NOT)&&(cn2=unary_expr(start,&start))) {*end=start;n->child[index++]=cn1;n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    free(n);
    free(cn1);
    free(cn2);
    n=NULL;
    cn1=NULL;
    cn2=NULL;
    return 0;
}
sync_node* mul_expr(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    int index=0;
    if((cn1=unary_expr(start,&start))&&(cn2=mul_expr1(start,&start))) {*end=start;n->child[index++]=cn1;if((long long)cn2!=1)n->child[index++]=cn2;return n;}
    free(n);
    free(cn1);
    free(cn2);
    n=NULL;
    cn1=NULL;
    cn2=NULL;
    return 0;
}
sync_node* mul_expr1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    int index=0;
    int t1=next(start,&start,cn1).attribute;
    if((t1==MUL||t1==DIV||t1==MOD)&&(cn2=unary_expr(start,&start))&&(cn3=mul_expr1(start,&start))) {*end=start;n->child[index++]=cn1;n->child[index++]=cn2;if((long long)cn3!=1)n->child[index++]=cn3;return n;}
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    n=NULL;
    cn1=NULL;
    cn2=NULL;
    cn3=NULL;
    return (long long)1;
}
sync_node* add_expr(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    int index=0;
    if((cn1=mul_expr(start,&start))&&(cn2=add_expr1(start,&start))) {*end=start;n->child[index++]=cn1;if((long long)cn2!=1)n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    free(n);
    free(cn1);
    free(cn2);
    n=NULL;
    cn1=NULL;
    cn2=NULL;
    return 0;
}
sync_node* add_expr1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    int t1=next(start,&start,cn1).attribute;
    if((t1==ADD||t1==SUB)&&(cn2=mul_expr(start,&start))&&(cn3=add_expr1(start,&start))) {*end=start;n->child[index++]=cn1;n->child[index++]=cn2;if((long long)cn3!=1)n->child[index++]=cn3;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    n=NULL;
    cn1=NULL;
    cn2=NULL;
    cn3=NULL;
    return (long long)1;
}
sync_node* expr(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* tc1=cn1;
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    int index=0;
    if((cn1=add_expr(start,&start))) {*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    free(n);
    free(cn1);
    n=NULL;
    cn1=NULL;
    return 0;
}


sync_node* var_def(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    char* temp=start;
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    int index=0;
    if(next(start,&start,cn1).type==ID&&next(start,&start,cn2).attribute==ASSIGN&&(cn3=expr(start,&start))) {*end=start;n->child[index++]=cn1;n->child[index++]=cn2;n->child[index++]=cn3;return n;}
    if(cn1->type==ID&&cn2->type==ASSIGN){raise_erro(start,"bad expr");*end=start;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    index=0;
    start=temp;
    if(next(start,&start,cn1).type==ID) {*end=start;n->child[index++]=cn1;return n;}
    if(cn1->type==ID){raise_erro(start,"bad identifier");*end=start;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    n=NULL;
    cn1=NULL;
    return 0;
}
sync_node* const_decl(char* start,char** end){
    char* temp=start;
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* cn4=malloc(sizeof(sync_node));
    sync_node* cn5=malloc(sizeof(sync_node));
    sync_node* cn6=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    memset(cn4,0,sizeof(sync_node));
    memset(cn5,0,sizeof(sync_node));
    memset(cn6,0,sizeof(sync_node));
    int index=0;
    if((next(start,&start,cn6).type==CONST)&&(next(start,&start,cn1).type==INT)&&(cn2=var_def(start,&start))){
        char* st=start;
        n->child[index++]=cn6;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        while(next(start,&start,cn3).type==COMMA&&(cn4=var_def(start,&start))) {
            st=start;
            n->child[index++]=cn3;
            n->child[index++]=cn4;
            cn3=malloc(sizeof(sync_node));
            cn4=malloc(sizeof(sync_node));
            memset(cn3,0,sizeof(sync_node));
            memset(cn4,0,sizeof(sync_node));
        }
        start=st;
        if(next(start,&start,cn5).type!=END){*end=start;free(n);free(cn1);free(cn2);free(cn3);free(cn4);free(cn5);return 0;}
        n->child[index++]=cn5;
        if(cn3==NULL||cn4==NULL){
            if(cn3!=NULL) {free(cn3);cn3=NULL;}
            if(cn4!=NULL) {free(cn4);cn4=NULL;}
        }
        *end=start;
        return n;
    }
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    free(cn4);
    free(cn5);
    free(cn6);
    n=NULL;
    return n;
}
sync_node* var_decl(char* start,char** end){
    char* temp=start;
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* cn4=malloc(sizeof(sync_node));
    sync_node* cn5=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    memset(cn4,0,sizeof(sync_node));
    memset(cn5,0,sizeof(sync_node));
    int index=0;
    if((next(start,&start,cn1).type==INT)&&(cn2=var_def(start,&start))){
        char* st=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        while(next(start,&start,cn3).type==COMMA&&(cn4=var_def(start,&start))) { 
            st=start;
            n->child[index++]=cn3;
            n->child[index++]=cn4;
            cn3=malloc(sizeof(sync_node));
            cn4=malloc(sizeof(sync_node));
            memset(cn3,0,sizeof(sync_node));
            memset(cn4,0,sizeof(sync_node));
        }
        start=st;
        if(next(start,&start,cn5).type!=END){*end=start;free(n);free(cn1);free(cn2);free(cn3);free(cn4);free(cn5);return 0;}
        n->child[index++]=cn5;
        if(cn3==NULL||cn4==NULL){
            if(cn3!=NULL) {free(cn3);cn3=NULL;}
            if(cn4!=NULL) {free(cn4);cn4=NULL;}
        }
        *end=start;
        return n;
    }
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    free(cn4);
    free(cn5);
    n=NULL;
    return n;
}
sync_node* decl(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* tc1=cn1;
    char* temp=start;
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    int index=0;
    if((cn1=var_decl(start,&start))) {*end=start;n->child[index++]=cn1;return n;}
    start=temp;
    index=0;
    cn1=tc1;
    if((cn1=const_decl(start,&start))) {*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    free(n);
    free(cn1);
    n=NULL;
    cn1=NULL;
    return 0;
}


sync_node* eq_exp(char* start,char** end);
sync_node* rel_exp(char* start,char** end);
sync_node* Land_exp(char* start,char** end);
sync_node* Lor_exp(char* start,char** end);
sync_node* cond(char* start,char** end);
sync_node* eq_exp1(char* start,char** end);
sync_node* rel_exp1(char* start,char** end);
sync_node* Land_exp1(char* start,char** end);
sync_node* Lor_exp1(char* start,char** end);

sync_node* eq_exp(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    int index=0;
    if((cn1=rel_exp(start,&start))&&(cn2=eq_exp1(start,&start))){*end=start;n->child[index++]=cn1;if((long long)cn2!=1)n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    free(n);
    free(cn1);
    free(cn2);
    return 0;
}
sync_node* eq_exp1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    int t=next(start,&start,cn1).attribute;
    if((t==UEQL||t==EQL)&&(cn2=rel_exp(start,&start))&&(cn3=eq_exp1(start,&start))){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;if((long long)cn3!=1)n->child[index++]=cn3;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    return (long long)1;
}
sync_node* rel_exp(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    int index=0;
    if((cn1=add_expr(start,&start))&&(cn2=rel_exp1(start,&start))){*end=start;n->child[index++]=cn1;if((long long)cn2!=1)n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    free(n);
    free(cn1);
    free(cn2);
    return 0;
}
sync_node* rel_exp1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    int t=next(start,&start,cn1).attribute;
    if((t==GRET||t==UGRET||t==UGRET_EQL||t==GRET_EQL)&&(cn2=add_expr(start,&start))&&(cn3=rel_exp1(start,&start))){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;if((long long)cn3!=1)n->child[index++]=cn3;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    return (long long)1;
}
sync_node* Land_exp(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    int index=0;
    if((cn1=eq_exp(start,&start))&&(cn2=Land_exp1(start,&start))){*end=start;n->child[index++]=cn1;if((long long)cn2!=1)n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    free(n);
    free(cn1);
    free(cn2);
    return 0;
}
sync_node* Land_exp1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    if(next(start,&start,cn1).attribute==AND&&(cn2=eq_exp(start,&start))&&(cn3=Land_exp1(start,&start))){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;if((long long)cn3!=1)n->child[index++]=cn3;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    return (long long)1;
}
sync_node* Lor_exp(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    int index=0;
    if((cn1=Land_exp(start,&start))&&(cn2=Lor_exp1(start,&start))){*end=start;n->child[index++]=cn1;if((long long)cn2!=1)n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    free(n);
    free(cn1);
    free(cn2);
    return 0;
}
sync_node* Lor_exp1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    if(next(start,&start,cn1).attribute==OR&&(cn2=Land_exp(start,&start))&&(cn3=Lor_exp1(start,&start))){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;if((long long)cn3!=1)n->child[index++]=cn3;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(n);
    free(cn1);
    free(cn2);
    free(cn3);
    return (long long)1;
}
sync_node* cond(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    int index=0;
    if((cn1=Lor_exp(start,&start))){*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    free(n);
    free(cn1);
    return 0;
}

sync_node* block(char* start,char** end);
sync_node* stmt(char* start,char** end);

sync_node* block(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* cn4=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    memset(cn4,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    sync_node* tc4=cn4;
    int index=0;
    char* temp=start;
    if(next(start,&start,cn1).type==LBRACE&&next(start,&start,cn2).type==RBRACE){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    start=temp;
    index=0;
    if(next(start,&start,cn1).type==LBRACE){
        n->child[index++]=cn1;
        char** a1=malloc(sizeof(void*));
        char** a2=malloc(sizeof(void*));
        while((cn2=stmt(start,a1))||(cn3=decl(start,a2))){
            if(cn2!=NULL){start=*a1;n->child[index++]=cn2;}
            else if(cn3!=NULL){start=*a2;n->child[index++]=cn3;}
            cn2=malloc(sizeof(sync_node));
            cn3=malloc(sizeof(sync_node));
            memset(cn2,0,sizeof(sync_node));
            memset(cn3,0,sizeof(sync_node));
        }
        free(a1);
        free(a2);
        if(next(start,&start,cn4).type!=RBRACE){*end=start;cn1=tc1;cn2=tc2;cn3=tc3;cn4=tc4;free(cn1);free(cn2);free(cn3);free(n);return 0;}
        n->child[index++]=cn4;
        *end=start;
        return n;  
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    free(cn1);
    free(cn2);
    free(cn3);
    free(cn4);
    free(n);
    return 0;
}
sync_node* stmt(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* cn4=malloc(sizeof(sync_node));
    sync_node* cn5=malloc(sizeof(sync_node));
    sync_node* cn6=malloc(sizeof(sync_node));
    sync_node* cn7=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    memset(cn4,0,sizeof(sync_node));
    memset(cn5,0,sizeof(sync_node));
    memset(cn6,0,sizeof(sync_node));
    memset(cn7,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    sync_node* tc4=cn4;
    sync_node* tc5=cn5;
    sync_node* tc6=cn6;
    sync_node* tc7=cn7;
    char* temp=start;
    int index=0;
    if(next(start,&start,cn1).type==IF&&next(start,&start,cn2).type==LPARES&&(cn3=cond(start,&start))&&next(start,&start,cn4).type==RPARES&&(cn5=stmt(start,&start))&&next(start,&start,cn6).type==ELSE
    &&(cn7=stmt(start,&start))){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        n->child[index++]=cn6;
        n->child[index++]=cn7;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    cn6=tc6;
    cn7=tc7;
    index=0;
    start=temp;
    if(next(start,&start,cn1).type==IF&&next(start,&start,cn2).type==LPARES&&(cn3=cond(start,&start))&&next(start,&start,cn4).type==RPARES&&(cn5=stmt(start,&start))){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    index=0;
    start=temp;
    if(next(start,&start,cn1).type==WHILE&&next(start,&start,cn2).type==LPARES&&(cn3=cond(start,&start))&&next(start,&start,cn4).type==RPARES&&(cn5=stmt(start,&start))){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    index=0;
    start=temp;
    if(next(start,&start,cn1).type==RET&&(cn2=expr(start,&start))&&next(start,&start,cn3).type==END){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    start=temp;
    if(next(start,&start,cn1).type==ID&&next(start,&start,cn2).attribute==ASSIGN&&(cn3=expr(start,&start))&&next(start,&start,cn4).type==END){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;n->child[index++]=cn3;n->child[index++]=cn4;return n;}
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    index=0;
    start=temp;
    if((cn1=block(start,&start))){*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    index=0;
    start=temp;
    if((cn1=expr(start,&start))&&next(start,&start,cn2).type==END){*end=start;n->child[index++]=cn1;n->child[index++]=cn2;return n;}
    cn1=tc1;
    cn2=tc2;
    if(next(start,&start,cn1).type==END){*end=start;n->child[index++]=cn1;return n;}
    cn1=tc1;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    cn6=tc6;
    cn7=tc7;
    free(cn1);
    free(cn2);
    free(cn3);
    free(cn4);
    free(cn5);
    free(cn6);
    free(cn7);
    free(n);
    return 0;
}


sync_node* func_def(char* start,char** end);
sync_node* func_parm(char* start,char** end);
sync_node* func_parms(char* start,char** end);
sync_node* func(char* start,char** end);

sync_node* func_def(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    sync_node* cn4=malloc(sizeof(sync_node));
    sync_node* cn5=malloc(sizeof(sync_node));
    sync_node* cn6=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    memset(cn4,0,sizeof(sync_node));
    memset(cn5,0,sizeof(sync_node));
    memset(cn6,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    sync_node* tc4=cn4;
    sync_node* tc5=cn5;
    sync_node* tc6=cn6;
    int index=0;
    char* temp=start;
    int t=next(start,&start,cn1).type;
    if((t==INT||t==VOID)&&next(start,&start,cn2).type==ID&&next(start,&start,cn3).type==LPARES&&next(start,&start,cn4).type==RPARES&&next(start,&start,cn5).type==END){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    start=temp;
    index=0;
    t=next(start,&start,cn1).type;
    if((t==INT||t==VOID)&&next(start,&start,cn2).type==ID&&next(start,&start,cn3).type==LPARES&&next(start,&start,cn4).type==RPARES&&(cn5=block(start,&start))){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    start=temp;
    index=0;
    t=next(start,&start,cn1).type;
    if((t==INT||t==VOID)&&next(start,&start,cn2).type==ID&&next(start,&start,cn3).type==LPARES&&(cn4=func_parms(start,&start))&&next(start,&start,cn5).type==RPARES&&(cn6=block(start,&start))){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        n->child[index++]=cn6;
        return n;
    }
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    cn6=tc6;
    index=0;
    start=temp;
    t=next(start,&start,cn1).type;
    if((t==INT||t==VOID)&&next(start,&start,cn2).type==ID&&next(start,&start,cn3).type==LPARES&&(cn4=func_parms(start,&start))&&next(start,&start,cn5).type==RPARES&&next(start,&start,cn6).type==END){
        *end=start;
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        n->child[index++]=cn3;
        n->child[index++]=cn4;
        n->child[index++]=cn5;
        n->child[index++]=cn6;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    cn4=tc4;
    cn5=tc5;
    cn6=tc6;
    free(cn1);
    free(cn2);
    free(cn3);
    free(cn4);
    free(cn5);
    free(cn6);
    free(n);
    return 0;
}
sync_node* func_parm(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    int index=0;
    if(next(start,&start,cn1).type==INT&&next(start,&start,cn2).type==ID){
        n->child[index++]=cn1;
        n->child[index++]=cn2;
        *end=start;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    free(cn1);
    free(cn2);
    free(n);
    return 0;
}
sync_node* func_parms(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    int index=0;
    if((cn1=func_parm(start,&start))){
        n->child[index++]=cn1;
        char* st;
        while(next(start,&start,cn2).type==COMMA&&(cn3=func_parm(start,&start))){
            st=start;
            n->child[index++]=cn2;
            n->child[index++]=cn3;
            sync_node* cn2=malloc(sizeof(sync_node));
            memset(cn2,0,sizeof(sync_node));
        }
        start=st;
        *end=start;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    cn3=tc3;
    free(cn1);
    free(cn2);
    free(cn3);
    free(n);
    return 0;
}

sync_node* comp_unit(char* start,char** end);
sync_node* comp_unit1(char* start,char** end);

sync_node* comp_unit(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    char* temp=start;
    int index=0;
    if((cn1=comp_unit1(start,&start))){
        if((long long)cn1!=1)
        n->child[index++]=cn1;
        *end=start;
        return n;
    }
    cn1=tc1;
    index=0;
    start=temp;
    if((cn1=comp_unit1(start,&start))){
        if((long long)cn1!=1)
        n->child[index++]=cn1;
        *end=start;
        return n;
    }
    cn1=tc1;
    free(cn1);
    free(n);
    return 0;
}
sync_node* comp_unit1(char* start,char** end){
    sync_node* n=malloc(sizeof(sync_node));
    sync_node* cn1=malloc(sizeof(sync_node));
    sync_node* cn2=malloc(sizeof(sync_node));
    sync_node* cn3=malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    memset(cn1,0,sizeof(sync_node));
    memset(cn2,0,sizeof(sync_node));
    memset(cn3,0,sizeof(sync_node));
    sync_node* tc1=cn1;
    sync_node* tc2=cn2;
    sync_node* tc3=cn3;
    char* temp=start;
    int index=0;
    if((cn1=decl(start,&start))&&(cn2=comp_unit1(start,&start))){
        n->child[index++]=cn1;
        if((long long)cn2!=1)
        n->child[index++]=cn2;
        *end=start;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    index=0;
    start=temp;
    if((cn1=func_def(start,&start))&&(cn2=comp_unit1(start,&start))){
        n->child[index++]=cn1;
        if((long long)cn2!=1)
        n->child[index++]=cn2;
        *end=start;
        return n;
    }
    cn1=tc1;
    cn2=tc2;
    free(cn1);
    free(cn2);
    free(n);
    return (long long)1;
}