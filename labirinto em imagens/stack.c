#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct stack_node stack_node;
struct stack_node
{
    struct Ponto data;
    stack_node *next;
};

struct Stack
{
    stack_node *begin;
    int size; // quantidade de elementos na lista
    int inf;
};

Stack *create_stack()
{
    Stack *st;
    st = malloc(sizeof(Stack));
    if (st == NULL)
    {
        return st;
    }
    st->begin = NULL;
    st->size = 0;

    return st;
}

int stack_free(Stack *st)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        stack_node *aux = st->begin;
        while (st->size != 0)
        {
            st->begin = aux->next;
            free(aux); //liberar cada posição
            aux = st->begin;
            st->size--;
        }
        free(st);
        return SUCCESS;
    }
}

int stack_push(Stack *st, struct Ponto al)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        stack_node *node;
        node = malloc(sizeof(stack_node));
        if (node == NULL)
        {
            return OUT_OF_MEMORY;
        }
        node->data = al;
        node->next = st->begin;
        st->begin = node;
        st->size++;
        return SUCCESS;
    }
}

int stack_pop(Stack *st)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    if (st->size == 0)
    {
        return OUT_OF_RANGE;
    }
    stack_node *aux = st->begin; 
    st->begin = aux->next;      

    free(aux);
    st->size--;

    return SUCCESS;
}

int stack_size(Stack *st)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    else
    {
        return st->size;
    }
}

int stack_find(Stack *st, struct Ponto *al)
{
    if (st == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    if (st->size == 0)
    {
        return OUT_OF_RANGE;
    }
    else
    {
        stack_node *aux = st->begin;
        *al = aux->data;
    }
    return SUCCESS;
}
