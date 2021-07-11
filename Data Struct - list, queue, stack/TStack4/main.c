#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../TStack3/TStack.h"

#define NOTFORMED -1
#define FORMED 0 
#define MAX 100

int bemFormada (char s[MAX]) {
    Stack *st;
    st = stack_create (MAX);
    struct chars c;
    int i = 0;
    int result;
    for (i = 0; s[i] != '\0'; ++i) {
        if(s[i] == ']'){
            if(stack_size(st) == 0)
                return NOTFORMED;
            else{
                stack_top(st, &c);
                if(c.ch != '[')
                    return NOTFORMED;
                else
                    stack_pop(st);
            }
        }
        else if(s[i] == ')'){
            if(stack_size(st) == 0)
                return NOTFORMED;
            else{
                stack_top(st, &c);
                if(c.ch != '(')
                    return -1;
                else
                    stack_pop(st);
            }
        }else{
            c.ch = s[i];
            stack_push(st, c);
        }  
    }
    result = stack_empty(st);
    stack_free(st);
    return result;
}

int main(void) {
    char formula[MAX];
    int ret;
    char resp;
    printf("\nDigite a fórmula: ");
    fgets(formula, 30, stdin);
    formula[strcspn(formula, "\n")] = '\0';
    ret = bemFormada(formula);
    if(ret != SUCCESS){
        printf("\nMal Formada\n");
    }else{
        printf("\nBem Formada\n");
    }
    printf("\nQuer verificar outra? y or n: ");
    scanf("%c", &resp);
    getchar();
    if (resp == 'y')
        return main();
    else
        return 0;
}
