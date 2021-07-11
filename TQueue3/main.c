#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TQueue.h"

#define OPMAX 8
#define OPMIN 0


void exibirOpcoes (void)
{
    printf("\n");
    printf("\n\n<< Lista com 10 alunos aleátorio >> \n\n");
    printf("1 - Criar Fila  \n");
    printf("2 - Inserir  \n");
    printf("3 - Remover \n");
    printf("4 - Retorna o Primeiro \n");
    printf("5 - Verifica se está vaiza  \n");
    printf("6 - Compactar\n");
    printf("7 - Tamanho Atual\n");
    printf("8 - Verificar quantos elementos fila suporta\n");
    printf("0 - Liberar lista e Sair \n\n");
}


unsigned int qualescolha (void)
{
    unsigned int escolha = 0;

    printf("\nEscolha uma opção: ");
    scanf("%u", &escolha); 
    while ( !(OPMIN <= escolha && escolha <= OPMAX))
    {
        printf("opção inválida!!!\n\n");
        printf("Digite uma opção: ");
        scanf("%d", &escolha);
    }
    return escolha;
}

void menu (){
  
  int ret, tamanho;
  struct student sl[10] = {{1,"Nícolas",9.5,7.8,8.5},
                          {2,"Gustavo",7.5,8.7,6.8},
                          {3,"Lucas",9.7,6.7,8.4},
                          {4,"Douglas",5.7,6.1,7.4},
                          {5,"Guilherme",9.0,5.1,8.4},
                          {6,"Paulo",6.7,6.4,7.5},
                          {7,"Jones",4.7,9.1,7.8},
                          {8,"Luís",8.7,6.8,7.5},
                          {9,"Maycon",6.5,6.8,9.4},
                          {10,"Bruno",9.7,7.3,8.6}};

          printf("tamanho da lista que deseja criar (min = 10)? ");
                scanf("%d", &tamanho);
                if (tamanho<10){
                  printf("\nError!\n\n");
                  return menu();}
                TQueue* fi = create_queue(tamanho);
                for(int i=0; i< 10; i++){
                  enqueue(fi, sl[i]);
                }

  while(1){

          exibirOpcoes();

          switch (qualescolha()){

              case 1:{
                    print_queue(fi);
              break;
              }

              case 2:{
                    struct student slaux;
                    printf("qual nome do aluno? ");
                    scanf("%s", slaux.name);
                    printf("qual numero de matricula? ");
                    scanf("%d", &slaux.id);
                    printf("Nota 1: ");
                    scanf("%f", &slaux.g1);
                    printf("Nota 2: ");
                    scanf("%f", &slaux.g2);
                    printf("Nota 3: ");
                    scanf("%f", &slaux.g3);
                    if(enqueue(fi, slaux) == SUCCESS){
                      printf("\n\n");print_queue(fi);}
                    else if(enqueue(fi, slaux) == INVALID_NULL_POINTER){
                      printf("\nFila não alocada ou Ponteiro invalido.");}
                    else if(enqueue(fi, slaux) == OUT_OF_MEMORY){
                      printf("\nFora de Memória.");}
              break;
              }
              case 3:{
                    if (dequeue(fi) == SUCCESS)
                      print_queue(fi);
                    else if (dequeue(fi) == EMPTY)
                      printf("\nLista vazia.");
                    else if (dequeue(fi) == INVALID_NULL_POINTER)
                      printf("\nFila não alocada ou Ponteiro invalido.");
              break;
              }
              
              case 4:{
                struct student slaux;
                    if(queue_front(fi, &slaux) == SUCCESS){
                      printf("\nMatrícula: %d\n", slaux.id);
                      printf("Nome: %s\n", slaux.name);
                      printf("Notas: %.2f, %.2f, %.2f\n", slaux.g1, slaux.g2, slaux.g3);}
                    else if (dequeue(fi) == EMPTY)
                      printf("\nLista vazia.");
                    else if (dequeue(fi) == INVALID_NULL_POINTER)
                      printf("\nFila não alocada ou Ponteiro invalido.");
                
              break;
              }
              
              case 5:{
                    if(queue_empty(fi) == EMPTY)
                      printf("\nA fila está vazia.\n");
                    else if (queue_empty(fi) == INVALID_NULL_POINTER)
                      printf("\nFila não alocada ou Ponteiro invalido.");
                    else if(queue_empty(fi) == NOT_EMPTY)
                      printf("\nFila não está vazia.");
              break;
              }
              case 6:{
                    fi = compact_queue(fi);
                    printf("\nTamanho suportado agora: %d.\n", suport_queue(fi));
              break;
              }
              case 7:{
                  printf("Tamanho Atual da Fila = %d", size(fi));
              break;
              }
              case 8:{
                  printf("Tamanho Suportado = %d", suport_queue(fi));
              break;
              }
              case 0:{
                free_queue(fi);
                return;
              }
          }
      }
  }

int main (void)
{
    menu();
    printf("\n Bye!");
    return 0;
}

