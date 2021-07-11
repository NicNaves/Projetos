#include <stdio.h>
#include <stdlib.h>
#include "TStack.h"
#include "../TLinkedlist/TLinkedList.h"


struct Stack{
    TLinkedList *data;    
};


Stack *create_stack(){
    Stack *st;
    st = malloc(sizeof(Stack));
    if(st == NULL)
        return INVALID_NULL_POINTER;
    st->data = list_create();
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
        return list_push_back(st->data,sl);
}


int stack_pop(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return list_pop_back(st->data);
}

int stack_size(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return list_size(st->data);
}

int stack_find_pos(Stack *st, int pos, struct student *sl){
     if(st == NULL)
        return INVALID_NULL_POINTER;    
    else
        return list_back(st->data,sl);
}
