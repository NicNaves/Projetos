
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TStack.h"



void opcao(void)
{
    printf("\n");
    printf("1 - Criar Lista  \n");
    printf("2 - Inserir  \n");
    printf("3 - Remover \n");
    printf("4 - Ultimo elemento \n");
    printf("5 - Verifica se está Vazia  \n");
    printf("6 - Tamanho \n");
    printf("7 - Mostrar elementos da pilha \n");
    printf("0 - Sair \n\n");
}

void pausar(){
  printf("ENTER para continuar\n");
  while(getchar()!='\n');
  return;
}

unsigned int op (void) //pega a escolha
{
    int op = 0;
    printf("\nEscolha uma opcao: ");
    scanf("%u", &op); 
    //printf("\n");
    while ( !(0 <= op && op <= 7))
    {
        printf("opcao inválida!!!\n\n");
        printf("Digite uma opcao: ");
        scanf("%d", &op);
    }
    return op;
}

void menu()
{
    Stack *st;
    struct chars c;
    int max;
    int ret;

   
    while(1){
    opcao();
    switch (op()){

    case 1:
      printf("Tamanho máximo da pilha? ");
      scanf(" %d", &max);
      st = stack_create(max);
      if(st == NULL)
        printf("Ponteiro inválido\n");
      else
        printf("Criada com sucesso\n");
      pausar();
      getchar();
    break;  

    case 2:
      
      if(st == NULL)
        printf("Ponteiro inválido\n");
      else{
        printf("Digite o carácter: ");
        scanf(" %c", &c.ch);
        ret = stack_push(st, c);
        if (ret == INVALID_NULL_POINTER)
          printf("Ponteiro inválido!\n");
        if (ret == OUT_OF_RANGE)
          printf("Fora de Alcance!\n");
        else
          printf("Adicionado!\n");
      }
      pausar();
      getchar();
    break;

    case 3:
      if(st == NULL)
        printf("Ponteiro inválido\n");
      else{
        ret = stack_pop(st);
        if (ret == INVALID_NULL_POINTER)
          printf("Ponteiro inválido!\n");
        if (ret == OUT_OF_RANGE)
          printf("Fora de Alcance!\n");
        else
          printf("Removido!\n");
      }
      pausar();
      getchar();
    break;

    case 4: 
      if(st == NULL)
        printf("Ponteiro inválido\n");
      else{
        ret = stack_top(st, &c);
        if (ret == INVALID_NULL_POINTER)
          printf("Ponteiro inválido!\n");
        if (ret == OUT_OF_RANGE)
          printf("Fora de Alcance!\n");
        else
        printf("\nUltima lerta: %c\n", c.ch);
      }
      pausar();
      getchar();
    break;

    case 5:
      if(st != NULL)
        ret = stack_empty(st);
      if(ret == SUCCESS)
        printf("Está vazia\n");
      else
        printf("Não está vazia\n");
      pausar();
      getchar();
    break;

    case 6:
      if(st == NULL)
        printf("Ponteiro inválido \n");
      ret = stack_size(st);
      printf("Tamanho = %d \n", ret);
      pausar();
      getchar();
    break;

    case 7:

      if(st != NULL){
        ret = print_stack(st);
        printf("\n\n");}
      else
        printf("Ponteiro inválido\n");
      pausar();
      getchar();
    break;

    case 0:
      if(st != NULL){
        stack_free(st);
        printf("Pìlha liberada\n");
      }
      return;
    break;
    }
  }
}

int main(void){
    menu();
    return 0;
}