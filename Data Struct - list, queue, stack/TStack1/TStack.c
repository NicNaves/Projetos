#include <stdio.h>
#include <stdlib.h>
#include "TStack.h"
#include "../TListSeq/TListSeq.h"


struct Stack{
    List_seq *data;    
};


Stack *create_stack(){
    Stack *st;
    st = malloc(sizeof(Stack));
    if(st == NULL)
        return INVALID_NULL_POINTER;
    st->data = create_list_seq();
    if(st->data == NULL){
        free(st);
        return INVALID_NULL_POINTER;
    }
    return st;
}

int stack_push(Stack *st, struct student sl){
    if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return  ins_list_seq_end(st->data,sl);
}

int stack_pop(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return rem_list_seq_end(st->data);
}


int stack_find_pos(Stack *st, int pos, struct student *sl){
    if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return consult_list_seq_pos(st->data,pos,sl);
}

int stack_size(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return size_list_seq(st->data);
}