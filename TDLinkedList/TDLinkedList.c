#include "TDLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXLETRAS  10

typedef struct DLNode DLNode;

struct TDLinkedList
{
  DLNode *begin;
  DLNode *end;
  int size;
};

struct DLNode
{
  struct student data;
  DLNode *next;
  DLNode *prev;
};

TDLinkedList *list_create()
{
  TDLinkedList *list;
  list = malloc(sizeof(TDLinkedList));
  if (list != NULL)
  {
    list->begin = NULL;
    list->end = NULL;
    list->size = 0;
  }
  return list;
}

int list_free(TDLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux = li->begin;
  DLNode *prev = NULL;
  while(aux != NULL){
    prev = aux;
    aux = aux->next;
    free(prev);
  }
  free(li);
  return SUCCESS;
}

int list_push_front(TDLinkedList *li, struct student sl){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *node;
  node = malloc(sizeof(DLNode));
  if (node == NULL)
    return OUT_OF_MEMORY;
  node->data = sl;
  node->prev = NULL;
  node->next = li->begin;
  if (li->begin == NULL){
      li->begin = node;
      li->end = node;
      li->size = 1; }
  else {
      li->begin->prev = node;
      li->begin = node;
      li->size = li->size + 1; }
    return SUCCESS;
}

int list_push_back(TDLinkedList *li, struct student sl){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *node;
  node = malloc(sizeof(DLNode));
  if (node == NULL)
    return OUT_OF_MEMORY;
  node->data = sl;
  node->next = NULL;
  node->prev = li->end;
  if (li->begin == NULL){
      li->begin = node;
      li->end = node;
      li->size = 1; }
  else {
      li->end->next = node;
      li->end = node;
      li->size = li->size + 1; }
    return SUCCESS;
}

int list_insert(TDLinkedList *li, int pos, struct student sl){
  if (li == NULL) 
    return INVALID_NULL_POINTER;
  if ((pos <= 0) || (pos > li->size + 1))
    return OUT_OF_RANGE;
  DLNode *node;
  node = malloc(sizeof(DLNode));
  if (node == NULL) 
    return OUT_OF_MEMORY;
  node->data = sl;
  if (li->size == 0) {
    node->prev = NULL;
    node->next = NULL;
    li->begin = node;
    li->end = node;
    li->size = 1;}
  else if (pos == 1){
    // insere na cabeça
    node->prev = NULL;
    node->next = li->begin;
    li->begin->prev = node;
    li->begin = node;
    li->size++;}
  else if (pos == li->size + 1) {
    // inserção no final
    node->next = NULL;
    node->prev = li->end;
    li->end->next = node;
    li->end = node;
    li->size++;}
  else {
    // inserção no meio da lista
    int i = 1;
    DLNode *aux;
    aux = li->begin;
    while (i < pos - 1) {
      aux = aux->next;
      i++;}
    node->prev = aux;
    node->next = aux->next;
    node->next->prev = node;
    aux->next = node;
    li->size++;
  }
  return SUCCESS;
}

int list_size(TDLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux = li->begin;
  if(aux == NULL)
    return OUT_OF_RANGE;
  else
    return li->size;
} 

int list_pop_front(TDLinkedList *li){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  else{
    if (li->size == 0)
      return OUT_OF_RANGE;
    if (li->size == 1) {
        free(li->end);
        li->begin = NULL;
        li->end = NULL;
        li->size = 0;}
    else {
        li->begin = li->begin->next;
        free(li->begin->prev);
        li->begin->prev = NULL;
        li->size--;}
    return SUCCESS;
  }
}

int list_pop_back(TDLinkedList *li){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  else{
    if (li->size == 0)
      return OUT_OF_RANGE;
    if (li->size == 1) {
        free(li->end);
        li->begin = NULL;
        li->end = NULL;
        li->size = 0;}
    else {
        li->end = li->end->prev;
        free(li->end->next);
        li->end->next = NULL;
        li->size = li->size - 1;}
    return SUCCESS;
  }
}

int list_erase(TDLinkedList *li, int pos){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux, *prev;
  aux = li->begin;
  int i = 0;
  while(i < pos-1){
    if (aux->next == NULL)
      return ELEM_NOT_FOUND;
    prev = aux;
    aux = aux->next;
    i++;}
  if (li->size == 1){
    // lista com um só elemento
    li->begin = NULL;
    li->end = NULL;
    li->size = 0;}
  else if (aux == li->begin){
    // início da lista
    li->begin = aux->next;
    li->begin->prev = NULL;}
  else if (aux == li->end){
    // fim de lista
    li->end = aux->prev;
    li->end->next = NULL;}
  else{
    // meio de lista
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;}
  free(aux);
  li->size--;
  return SUCCESS;
}

int list_erase_mat(TDLinkedList *li, int id){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux;
  aux = li->begin;
  while (aux->data.id != id){
    if (aux->next == NULL)
      return ELEM_NOT_FOUND;
    aux = aux->next;
  }
  if (li->size == 1){
    // lista com um só elemento
    li->begin = NULL;
    li->end = NULL;}
  else if (aux == li->begin){
    // início da lista
    li->begin = aux->next;
    li->begin->prev = NULL;}
  else if (aux == li->end){
    // fim de lista
    li->end = aux->prev;
    li->end->next = NULL;}
  else{
    // meio de lista
    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;}
  free(aux);
  li->size--;
  return SUCCESS;
}

int list_find_mat(TDLinkedList *li, int id, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux;
  aux = li->begin;
  while(aux->data.id != id ){
    if (aux->next == NULL)
      return ELEM_NOT_FOUND;
    aux = aux->next;
  }
  *sl = aux->data;
  return SUCCESS;
}

int list_find_pos(TDLinkedList *li, int pos, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux; 
  aux = li->begin;
  int i = 0;
  while(i < pos-1){
    if (aux->next == NULL)
      return ELEM_NOT_FOUND;
    aux = aux->next;
    i++;
  }
  *sl = aux->data;
  return SUCCESS;
}

int list_front(TDLinkedList *li, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->begin == NULL)
     return OUT_OF_RANGE;
  DLNode *aux;
  aux = li->begin;
  *sl = aux->data;  
  return SUCCESS;
}

int list_back(TDLinkedList *li, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_RANGE;
  DLNode *aux;
  aux = li->end;
  *sl = aux->data;
  return SUCCESS;
}

int list_get_pos(TDLinkedList *li, int id, int *pos){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  int i = 1;
  *pos = i;
  DLNode *aux; 
  aux = li->begin;
  if(id == aux->data.id)
    return SUCCESS;
  while(id != aux->data.id){
    if (aux->next == NULL)
      return ELEM_NOT_FOUND;
    aux = aux->next;
    i++;
    *pos = i;
  }
  return SUCCESS;
}

int list_print_foward (TDLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux = li->begin;
  char Maxletra[10];
  printf("%s%*s%20s\n", "Id ",-MAXLETRAS, "Nome", "Notas");
  printf("------------------------------------------------\n"); 
  while(aux != NULL){
    printf("%d ",  aux->data.id);
    printf("%*s ",-MAXLETRAS, aux->data.name);
    printf("%15.1f %5.1f %5.1f\n",aux->data.g1,aux->data.g2,aux->data.g3); 
    printf("------------------------------------------------\n"); 
    aux = aux->next;}
  return SUCCESS;
}

int list_print_reverse(TDLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  DLNode *aux = li->end;
  char Maxletra[10];
  printf("%s%*s%20s\n", "Id ",-MAXLETRAS, "Nome", "Notas");
  printf("------------------------------------------------\n"); 
  while (aux != NULL){
    printf("%d ",  aux->data.id);
    printf("%*s ",-MAXLETRAS, aux->data.name);
    printf("%15.1f %5.1f %5.1f\n",aux->data.g1,aux->data.g2,aux->data.g3); 
    printf("------------------------------------------------\n"); 
    aux = aux->prev;}
  return SUCCESS;
}

