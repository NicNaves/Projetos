#define SUCCESS 0
#define INVALID_NULL_POINTER -1 //sempre que a função receber null
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define ERRO_SORTED -5

typedef struct Stack Stack;
#include "Ponto.h"

Stack *create_stack();
int stack_free(Stack *st);
int stack_push(Stack *st, struct Ponto al);  //insere no final
int stack_pop(Stack *st);                    //remove final
int stack_size(Stack *st);                   //tamanho da pilha ou se está vazia
int stack_find(Stack *st, struct Ponto *al); //consulta topo
