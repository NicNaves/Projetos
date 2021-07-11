#ifndef Stackh
#define Stackh

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3


typedef struct Stack Stack;
#include "../aluno.h"

Stack *create_stack();

int stack_push(Stack *st, struct student sl);
int stack_pop(Stack *st);
int stack_find_pos(Stack *st, int pos, struct student *sl);
int stack_size(Stack *st);

#endif