#include "lex_analy.h"

void print_stack(sync_linktable* stack,char* start){
    int i=stack->num;
    linknode* ptr=stack->tail;
    while(i>0){
        print_type(ptr);
        printf("   ");
        ptr=ptr->pre;
        i--;
    }
    printf("  %s\n",start);
    fflush(stdin);
}

void set_child(linknode* t,sync_linktable* stack,int type){
    t->node->child[t->node->index]=(sync_node*)malloc(sizeof(sync_node));
    memset(t->node->child[t->node->index],0,sizeof(sync_node));
    t->node->child[t->node->index]->type=type;
    push(stack,t->node->child[t->node->index++]);
}

void set_child_TK(linknode* t,sync_linktable* stack,int type,int attribute){
    t->node->child[t->node->index]=(sync_node*)malloc(sizeof(sync_node));
    memset(t->node->child[t->node->index],0,sizeof(sync_node));
    t->node->child[t->node->index]->type=TOKEN;
    t->node->child[t->node->index]->tk.type=type;
    t->node->child[t->node->index]->tk.attribute=attribute;
    push(stack,t->node->child[t->node->index++]);
}

sync_node* sync(char* start,char** end){
    char* ta;
    sync_node ttt;
    sync_linktable stack;
    sync_link_init(&stack);
    sync_node* n=(sync_node*)malloc(sizeof(sync_node));
    memset(n,0,sizeof(sync_node));
    sync_node tt;
    char* temp;
    push(&stack,n);
    top(&stack)->node->type=COMUNIT;
    int state=COMUNIT;
    int i=10000;
    while(stack.num!=0&&i>0){
        //i--;
        while(*start==13||*start==32) start++;
        //print_stack(&stack,start);
        switch(state){
            case TOKEN:
                if(top(&stack)->node->tk.type!=RELOP&&top(&stack)->node->tk.type!=OP&&top(&stack)->node->tk.type==next(start,&temp,&tt).type){
                    linknode* t= top(&stack);
                    start=temp;
                    t->node->tk=tt.tk;
                    pop(&stack);
                    state=top(&stack)->node->type;
                    break;
                }
                if((top(&stack)->node->tk.type==RELOP||top(&stack)->node->tk.type==OP)&&top(&stack)->node->tk.attribute==next(start,&temp,&tt).attribute){
                    linknode* t= top(&stack);
                    start=temp;
                    t->node->tk=tt.tk;
                    pop(&stack);
                    state=top(&stack)->node->type;
                    break;
                }
            case EXP:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,ADDEXP);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case ADDEXP:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,ADDEXP1);
                    set_child(t,&stack,MULEXP);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case ADDEXP1:
                if(next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,ADDEXP1);
                    set_child(t,&stack,MULEXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==MUL
                ||next(start,&temp,&tt).attribute==DIV
                ||next(start,&temp,&tt).attribute==MOD
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).type==COMMA
                ||next(start,&temp,&tt).type==END
                ||next(start,&temp,&tt).attribute==OR
                ||next(start,&temp,&tt).attribute==AND
                ||next(start,&temp,&tt).attribute==EQL
                ||next(start,&temp,&tt).attribute==UEQL
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).attribute==GRET
                ||next(start,&temp,&tt).attribute==UGRET
                ||next(start,&temp,&tt).attribute==UGRET_EQL
                ||next(start,&temp,&tt).attribute==GRET_EQL){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            case MULEXP:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,MULEXP1);
                    set_child(t,&stack,UNARYEXP);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case MULEXP1:
                if(next(start,&temp,&tt).attribute==MUL
                ||next(start,&temp,&tt).attribute==DIV
                ||next(start,&temp,&tt).attribute==MOD
                ){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,MULEXP1);
                    set_child(t,&stack,UNARYEXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).type==COMMA
                ||next(start,&temp,&tt).type==END
                ||next(start,&temp,&tt).attribute==OR
                ||next(start,&temp,&tt).attribute==AND
                ||next(start,&temp,&tt).attribute==EQL
                ||next(start,&temp,&tt).attribute==UEQL
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).attribute==GRET
                ||next(start,&temp,&tt).attribute==UGRET
                ||next(start,&temp,&tt).attribute==UGRET_EQL
                ||next(start,&temp,&tt).attribute==GRET_EQL){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case UNARYEXP:
                if(next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,RPARES,0);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==NUMBER){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==ID){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,IDPREFIX);                
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==NOT){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,UNARYEXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case IDPREFIX:
                if(next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,RPARES,0);
                    set_child(t,&stack,FUNCRPARAM);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==MUL
                ||next(start,&temp,&tt).attribute==DIV
                ||next(start,&temp,&tt).attribute==MOD
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).type==COMMA
                ||next(start,&temp,&tt).type==END
                ||next(start,&temp,&tt).attribute==OR
                ||next(start,&temp,&tt).attribute==AND
                ||next(start,&temp,&tt).attribute==EQL
                ||next(start,&temp,&tt).attribute==UEQL
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).attribute==GRET
                ||next(start,&temp,&tt).attribute==UGRET
                ||next(start,&temp,&tt).attribute==UGRET_EQL
                ||next(start,&temp,&tt).attribute==GRET_EQL) {
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case FUNCRPARAM:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,FUNCRPREFIX);
                    set_child(t,&stack,EXP);
                    state=top(&stack)->node->type;
                    break;
                }
            case FUNCRPREFIX:
                if(next(start,&temp,&tt).type==COMMA){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,FUNCRPARAM);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RPARES){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            case COND:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,LOREXP);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==NOT){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,RPARES,0);  
                    set_child(t,&stack,COND);
                    set_child_TK(t,&stack,LPARES,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case LOREXP:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,LOREXP1);
                    set_child(t,&stack,LANDEXP);
                    state=top(&stack)->node->type;
                    break;
                }
            case LOREXP1:
                if(next(start,&temp,&tt).attribute==OR){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,LOREXP1);
                    set_child(t,&stack,LANDEXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).type==END){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            case LANDEXP:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,LANDEXP1);
                    set_child(t,&stack,RELEXP);
                    state=top(&stack)->node->type;
                    break;
                }
            case LANDEXP1:
                if(next(start,&temp,&tt).attribute==AND){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,LANDEXP1);
                    set_child(t,&stack,RELEXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==OR
                ||next(start,&temp,&tt).type==RPARES
                ||next(start,&temp,&tt).type==END){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            case RELEXP:
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES
                ){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,RELEXP1);
                    set_child(t,&stack,ADDEXP);
                    state=top(&stack)->node->type;
                    break;
                }
            case RELEXP1:
                if(next(start,&temp,&tt).attribute==GRET
                ||next(start,&temp,&tt).attribute==UGRET
                ||next(start,&temp,&tt).attribute==UGRET_EQL
                ||next(start,&temp,&tt).attribute==GRET_EQL
                ||next(start,&temp,&tt).attribute==EQL
                ||next(start,&temp,&tt).attribute==UEQL){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,ADDEXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case VAR_DECL:
                if(next(start,&temp,&tt).type==INT){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child(t,&stack,IDARRY);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case IDARRY:
                if(next(start,&temp,&tt).type==ID){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,IDARRYPREFIX);
                    set_child(t,&stack,DATADECLPREFIX);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case IDARRYPREFIX:
                if(next(start,&temp,&tt).type==COMMA){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,IDARRY);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==END){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case CONST_DECL:
                if(next(start,&temp,&tt).type==CONST){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,CONSTPREFIX);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,OP,ASSIGN);
                    set_child_TK(t,&stack,ID,0);
                    set_child_TK(t,&stack,INT,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case CONSTPREFIX:
                if(next(start,&temp,&tt).type==COMMA){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,CONSTPREFIX);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,OP,ASSIGN);
                    set_child_TK(t,&stack,ID,0);
                    push(&stack,t->node->child[t->node->index++]);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==END){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case DATADECLPREFIX:
                if(next(start,&temp,&tt).attribute==ASSIGN){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==END
                ||next(start,&temp,&tt).type==COMMA){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            case DATADECL:
                 if(next(start,&temp,&tt).type==CONST){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,CONST_DECL);
                    state=top(&stack)->node->type;
                    break;
                 }
                 if(next(start,&temp,&tt).type==INT){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,VAR_DECL);
                    state=top(&stack)->node->type;
                    break;
                 }
            case DECL:
                if(next(start,&temp,&tt).type==INT){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,DECLPREFIX);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==VOID&&next(temp,&ta,&ttt).type==ID){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,VOIDDECLPREFIX);
                    set_child_TK(t,&stack,RPARES,0);
                    set_child(t,&stack,PARA);
                    set_child_TK(t,&stack,LPARES,0);
                    set_child_TK(t,&stack,ttt.tk.type,ttt.tk.attribute);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==CONST){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,CONST_DECL);
                    state=top(&stack)->node->type;
                    break;
                }
            case VOIDDECLPREFIX:
                if(next(start,&temp,&tt).type==LBRACE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,BLOCK);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==END){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case DECLPREFIX:
                if(next(start,&temp,&tt).type==ID){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,DECLPREPREFIX);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case DECLPREPREPREFIX:
                if(next(start,&temp,&tt).type==LBRACE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,BLOCK);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==END){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case DECLPREPREFIX:
                if(next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,DECLPREPREPREFIX);
                    set_child_TK(t,&stack,RPARES,0);
                    set_child(t,&stack,PARA);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).attribute==ASSIGN){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child(t,&stack,IDARRYPREFIX);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==COMMA){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child(t,&stack,IDARRY);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==END){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case PARA:
                if(next(start,&temp,&tt).type==INT){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,PARAPREFIX);
                    set_child_TK(t,&stack,ID,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RPARES){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case PARAPREFIX:
                if(next(start,&temp,&tt).type==COMMA){
                linknode* t= top(&stack);
                pop(&stack);
                set_child(t,&stack,PARA);
                set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                state=top(&stack)->node->type;
                break;
                }
                if(next(start,&temp,&tt).type==RPARES){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case STMT:
                if(next(start,&temp,&tt).type==BREAK){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==CONTINUE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==ID&&next(temp,&ta,&ttt).attribute==ASSIGN){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,OP,ASSIGN);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==NUMBER
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).attribute==ADD
                ||next(start,&temp,&tt).attribute==SUB
                ||next(start,&temp,&tt).attribute==NOT
                ||next(start,&temp,&tt).type==LPARES){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child(t,&stack,EXP);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==LBRACE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,BLOCK);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==IF){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,IFPREFIX);
                    set_child(t,&stack,STMT);
                    set_child_TK(t,&stack,RPARES,0);
                    set_child(t,&stack,COND);
                    set_child_TK(t,&stack,LPARES,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==WHILE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,STMT);
                    set_child_TK(t,&stack,RPARES,0);
                    set_child(t,&stack,COND);
                    set_child_TK(t,&stack,LPARES,0);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RET&&next(temp,&ta,&ttt).type==END){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,ttt.tk.type,ttt.tk.attribute);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RET){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,END,0);
                    set_child(t,&stack,EXP);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RBRACE){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case IFPREFIX:
                if(next(start,&temp,&tt).type==ELSE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,STMT);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RBRACE
                ||next(start,&temp,&tt).type==INT
                ||next(start,&temp,&tt).type==CONST
                ||next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).type==WHILE
                ||next(start,&temp,&tt).type==IF
                ||next(start,&temp,&tt).type==BREAK
                ||next(start,&temp,&tt).type==CONTINUE
                ||next(start,&temp,&tt).type==LBRACE
                ||next(start,&temp,&tt).type==RET){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            case BLOCK:
                if(next(start,&temp,&tt).type==LBRACE){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child_TK(t,&stack,RBRACE,0);
                    set_child(t,&stack,BLOCKITEM);
                    set_child_TK(t,&stack,tt.tk.type,tt.tk.attribute);
                    state=top(&stack)->node->type;
                    break;
                }
            case BLOCKITEM:
                if(next(start,&temp,&tt).type==INT
                ||next(start,&temp,&tt).type==CONST){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,BLOCKITEM);
                    set_child(t,&stack,DATADECL);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==ID
                ||next(start,&temp,&tt).type==LBRACE
                ||next(start,&temp,&tt).type==IF
                ||next(start,&temp,&tt).type==WHILE
                ||next(start,&temp,&tt).type==RET
                ||next(start,&temp,&tt).type==CONTINUE
                ||next(start,&temp,&tt).type==BREAK){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,BLOCKITEM);
                    set_child(t,&stack,STMT);
                    state=top(&stack)->node->type;
                    break;
                }
                if(next(start,&temp,&tt).type==RBRACE){
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
                break;
            case COMUNIT:
                if(next(start,&temp,&tt).type==VOID
                ||next(start,&temp,&tt).type==INT
                ||next(start,&temp,&tt).type==CONST){
                    linknode* t= top(&stack);
                    pop(&stack);
                    set_child(t,&stack,COMUNIT);
                    set_child(t,&stack,DECL);
                    state=top(&stack)->node->type;
                    break;
                }
                else{
                    pop(&stack)->node->empty=1;
                    state=top(&stack)->node->type;
                    break;
                }
            default:
                    break;
             //printf("%d\n",*(temp-1));
        }
    }
    *end=start;
    return n;
}