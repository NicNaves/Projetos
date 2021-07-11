#ifndef Stackh
#define Stackh

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define NOT_FULL -4

struct chars {
    char ch;
};


typedef struct stack Stack;

Stack* stack_create(int max);
int stack_free(Stack *st);
int stack_push(Stack *st, struct chars al);
int stack_pop(Stack *st);
int stack_top(Stack *st, struct chars *al);
int stack_empty(Stack *st);
int stack_size(Stack *st);
int print_stack(Stack *st);


#endif