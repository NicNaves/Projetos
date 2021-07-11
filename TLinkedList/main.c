#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TLinkedList.h"

int main(){
  struct student s[3] = 
  {{2,"Nícolas",9.5,7.8,8.5},
  {4,"Gustavo",7.5,8.7,6.8},
  {5,"Lucas",9.7,6.7,8.4},};

  struct student sl[3] =
  {{1,"Diego",9.5,5.8,10.0},
  {6, "Paulo", 7.4,8.5,8.8},
  {3, "Maycon", 7.8,9.5,8.9}};

  struct student aux;
  
  TLinkedList *list;
  list = list_create();
  int ret;
  int i = 0;
  int pos=0;
  
  printf("\nIniciando com 3 alunos em ordem \n\n");
  while (i<3){
    if((ret = list_insert_sorted(list, s[i])) == SUCCESS)
      i++;
    else if (ret == INVALID_NULL_POINTER)
      printf("\nPonteiro inválido.");
    else if (ret == OUT_OF_MEMORY)
      printf("\nSem Memória.");
    else if (ret == OUT_OF_RANGE)
      printf("\nFora de alcance.");
  }
  list_print(list);

  printf("\n\n Adicionando no inicio \n\n");
  if((ret = list_push_front(list,  sl[0])) == SUCCESS)
    list_print(list);
  else
    printf("\nPonteiro inválido.");

  
  printf("\n\n Adicionando no final \n\n");
  if((ret = list_push_back(list, sl[1])) == SUCCESS)
    list_print(list);
  else
    printf("\nPonteiro inválido.");
  
  printf("\n\n Adicionando na posição 3 \n\n");
  if((ret = list_insert(list, 3, sl[2])) == SUCCESS)
    list_print(list);
  else if (ret == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");
  else if (ret == OUT_OF_MEMORY)
    printf("\nSem Memória.");
  

  printf("\n\n Consulta quem está na posição 3 \n\n");
  if((ret = list_find_pos(list, 3, &aux)) == SUCCESS)
    printf("Id: %d \nNome: %s\nNotas: ( %.2f, %.2f, %.2f )\n",aux.id, aux.name, aux.g1, aux.g2,aux.g3);
  else if(ret == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");
  else if (ret == ELEM_NOT_FOUND)
    printf("\nElemento não encontrado.");
  
  printf("\n\n Consulta quem possui matrícula 2  \n\n");
  if((ret = list_find_mat(list,  2, &aux)) == SUCCESS)
    printf("Id: %d \nNome: %s\nNotas: ( %.2f, %.2f, %.2f )\n",aux.id, aux.name, aux.g1, aux.g2,aux.g3);
  else if(ret == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");
  else if (ret == ELEM_NOT_FOUND)
    printf("\nElemento não encontrado.");
  
  printf("\n\n Consulta quem é o primeiro \n\n");
  if((ret = list_front(list, &aux)) == SUCCESS)
    printf("Id: %d \nNome: %s\nNotas: ( %.2f, %.2f, %.2f )\n",aux.id, aux.name, aux.g1, aux.g2,aux.g3);
  else if (ret == OUT_OF_RANGE)
    printf("\nFora de alcance.");
  else
    printf("\nPonteiro inválido.");
  
  printf("\n\n Consulta quem é o último \n\n");
  if((ret = list_back(list, &aux)) == SUCCESS)
    printf("Id: %d \nNome: %s\nNotas: ( %.2f, %.2f, %.2f )\n",aux.id, aux.name, aux.g1, aux.g2,aux.g3);
  else if (ret == OUT_OF_RANGE)
    printf("\nFora de alcance.");
  else
    printf("\nPonteiro inválido.");
  
  printf("\n\n Consulta qual posição a matrícula 2 está \n\n");
  if((ret = list_get_pos(list, 2,  &pos)) == SUCCESS)
    printf("Posição: %d", pos);
  else if(ret == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");
  else if (ret == ELEM_NOT_FOUND)
    printf("\nElemento não encontrado.");


  printf("\n\n Remove no inicio \n\n");
  if((ret = list_pop_front(list)) == SUCCESS)
    list_print(list);
  else
    printf("\nPonteiro inválido.");
  
  printf("\n\n Remove no final \n\n");
  if((ret = list_pop_back(list)) == SUCCESS)
    list_print(list);
  else
    printf("\nPonteiro inválido.");
  
  printf("\n\n Remove a posição 2\n\n");
  if((ret = list_erase(list, 2)) == SUCCESS)
    list_print(list);
  else if(ret == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");
  else if (ret == ELEM_NOT_FOUND)
    printf("\nElemento não encontrado.");

  
  if((ret = list_size(list)) == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");
  else if (ret == OUT_OF_RANGE)
    printf("\nFora de alcance.");
  else
     printf("\n\n Tamanho da Lista: %d\n\n", list_size(list));

  if((ret = list_free(list)) == INVALID_NULL_POINTER)
    printf("\nPonteiro inválido.");

  return 0;
}

