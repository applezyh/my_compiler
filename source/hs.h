#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>

#define HSSIZE 7;
bool compare_arry(char* a,char* b,int size){
    int i;
    for(i=0;i<size;i++){
        if(a[i]!=b[i]) return 0;
    }
    return 1;
}
typedef struct node
{
    /* data */
    char* data;
    struct node* next;
    int data_size;
    int type;
    
}node;
void setname(node* n,char* name,int size){
    n->data=(char*)malloc((size+1)*sizeof(char));
    char* data_ptr=n->data;
    while(data_ptr!=n->data+size){
        *data_ptr++=*name++;
    }
    n->data[size]='\0';
    n->data_size=size;
}


typedef struct link
{
    /* data */
    node* head;

}linktable;
void link_init(linktable* l){
    l->head=(node*)malloc(sizeof(node));
}
node* link_insert(linktable* l,char* name,int size){
    if(l->head==NULL){l->head=(node*)malloc(sizeof(node));}
    node* t=(node*)malloc(sizeof(node));
    setname(t,name,size);
    node* n=l->head->next;
    l->head->next=t;
    t->next=n;
    return t;
}
node* link_find(linktable* l,char* name,int size){
    node* guard=l->head->next;
    while(guard!=NULL){
        if(guard->data_size==size){
            if(compare_arry(guard->data,name,size)) return guard;
        }
        guard=guard->next;
    }
    return NULL;
}


int hsfunc(char* name,int size){
    int ret=0;
    char* name_ptr=name;
    int i=1;
    while(name_ptr!=name+size){
        ret+=(*name_ptr++)<<i;
    }
    return ret;
}

typedef struct hs
{
    /* data */
    linktable* hs_table;
    int size;
    int num;

}hstable;
void hs_init(hstable* hs){
    hs->size=HSSIZE;
    hs->hs_table=(linktable*)malloc(hs->size*sizeof(linktable));
    int i;
    for(i=0;i<hs->size;i++){
        link_init(&(hs->hs_table[i]));
    }
}
node* hs_insert(hstable* hs,char* name,int size){
    node* ret;
    int index=hsfunc(name,size)%hs->size;
    if((ret=link_find(&(hs->hs_table[index]),name,size))!=NULL) return ret;
    hs->num++;
    return link_insert(&(hs->hs_table[index]),name,size);
}