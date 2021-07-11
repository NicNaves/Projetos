#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TStack.h"

struct stack{
    int size;
    int max;
    struct chars* data;
};


Stack* stack_create(int max){
    Stack* st;
    st = malloc(sizeof(Stack));
    if(st == NULL)
        return st;
    st->size = 0;
    st->max = max;
    st->data = malloc(sizeof(char)*max);
    if(st->data == NULL){
        free(st);
        st = NULL;}
    return st;
}

int stack_free(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else{
        free(st->data);
        free(st);
        return SUCCESS;
    }
}

int stack_push(Stack *st, struct chars al){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if (st->size == st->max)
        return OUT_OF_RANGE;
    else{
        char take;
        st->data[st->size].ch  = al.ch;
        st->size++;
        return SUCCESS;
    }
}

int stack_pop(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if(st->size == 0)
        return OUT_OF_RANGE;
    else{
        st->size--;
        return SUCCESS;
    }
}


int stack_top(Stack *st, struct chars *al){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if(st->size == 0)
        return OUT_OF_RANGE;
    else{
        al->ch = st->data[st->size-1].ch;
        return SUCCESS;
    }
}

int stack_empty(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if(st->size == 0)
        return SUCCESS;
    else
        return 1;
}

int stack_size(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    else
        return st->size;
}


int print_stack(Stack *st){
    if(st == NULL)
        return INVALID_NULL_POINTER;
    if(st->size == 0)
        return OUT_OF_RANGE;
    int i = 0;
    while( i < st->size){
        printf("%c\n", st->data[i].ch);
        i++;}
    return SUCCESS;
}
