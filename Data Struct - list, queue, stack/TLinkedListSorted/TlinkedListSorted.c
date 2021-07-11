#include "TLinkedListSorted.h"
#include <stdlib.h>
#include<stdio.h>
#define MAXLETRAS  10

typedef struct list_node list_node;

struct list_node {
    struct student data;
    list_node *next;
};

struct TLinkedList {   
  list_node *head; 
  int size;
  int sorted; 
  };  


TLinkedList* list_create(int x){
  TLinkedList *list;
  list = malloc(sizeof(TLinkedList));
  if (list != NULL){
    list->head = NULL;
    list->size = 0;
    list->sorted = x;
  }
    return list;
};

int list_free(TLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  list_node *aux = li->head;
  list_node *previous = NULL;
  while(aux != NULL){
    previous = aux;
    aux = aux->next;
    free(previous);
    li->size--;
  }
  free(li);
  return SUCCESS;
}

int list_push_front(TLinkedList *li, struct student sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->sorted == 1)
    return SORTED;
  list_node *new_node = malloc(sizeof(struct list_node));
  if(new_node == NULL)
    return INVALID_NULL_POINTER;
  new_node->data = sl; 
  new_node->next = li->head;
  li->head = new_node;
  li->size++;
  return SUCCESS;
}

int list_push_back(TLinkedList *li, struct student sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->sorted == 1)
    return SORTED;
  list_node *new_node = malloc(sizeof(struct list_node));
  if(new_node == NULL)
    return INVALID_NULL_POINTER;
  new_node->data = sl; 
  new_node->next = NULL;
  if(li->head == NULL)
    li->head = new_node;
    li->size++;
    return SUCCESS;
  list_node *aux = li->head;
  while(aux->next != NULL){
    aux = aux->next;
  }
  aux->next = new_node;
  li->size++;
  return SUCCESS;
}

int list_insert(TLinkedList *li, int pos, struct student sl){
  if(li == NULL)
      return INVALID_NULL_POINTER;
  if(li->sorted == 1)
    return SORTED;
  if ((pos <= 0) || (pos > li->size + 1))
    return OUT_OF_RANGE;
  else{
    list_node *node = malloc(sizeof(list_node));
    if(node == NULL)
      return OUT_OF_MEMORY;
    else{
      node->data = sl;
      if(li->head == NULL){
        node->next = NULL;
        li->head = node;}
      else{
      list_node *aux,*previous; 
      aux = li->head;
      int i = 1;
      while(pos > i){
        previous = aux;
        aux = aux->next;
        i++;
      }
    previous->next = node;
    node->next = aux;
    li->size++;
      }
    }
  }
  return SUCCESS;
}


int list_insert_sorted(TLinkedList *li, struct student sl){
  if (li == NULL)
    return INVALID_NULL_POINTER;
  if (li->sorted == 0)
    return SORTED;
  else{
    list_node *node;
    node = malloc(sizeof(list_node));
    if (node == NULL)
      return OUT_OF_MEMORY;
    else {
      node->data = sl;
      if (li->head == NULL){
        node->next = NULL;
        li->head = node;}
      else{
        list_node *aux, *previous;
        aux = li->head;
        while (aux != NULL &&  aux->data.id < sl.id ) {
          previous = aux;
          aux = aux->next;
        }
        if (aux == li->head) {
          node->next = li->head;
          li->head = node;}
        else {
          previous->next = node;
          node->next = aux;
        }
      }
      li->size++;
      return SUCCESS;
    }
  }
}

int list_size(TLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  list_node *aux = li->head;
  if(aux == NULL)
    return OUT_OF_RANGE;
  return li->size;
}


int list_pop_front(TLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if (li->size == 0)
      return OUT_OF_RANGE;
  list_node *aux = li->head;
  li->head = aux->next;
  free(aux);
  li->size--;
  return SUCCESS;
}

int list_pop_back(TLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if (li->size == 0)
      return OUT_OF_RANGE;
  if(li->head->next == NULL){
    free(li->head);
    li->head = NULL;}
  list_node *previous; 
  list_node *aux = li->head;
  while(aux->next != NULL){
    previous = aux;
    aux = aux->next;
  }
  previous->next = NULL;
  free(aux->next);
  li->size--;
  return SUCCESS;
}

int list_erase(TLinkedList *li, int pos){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  list_node *aux,*previous;
  aux = li->head;
  if (pos == 1){
    li->head = aux->next;
    free(aux);
    li->size--;
    return SUCCESS;
  }
  else{
    int i = 0;
    while(i < pos-1){
      if (aux->next == NULL)
        return ELEM_NOT_FOUND;
      previous = aux;
      aux = aux->next;
      i++;
  }
  previous->next = aux->next;
  free(aux);
  li->size--;
  return SUCCESS;
  }
}


int list_find_pos(TLinkedList *li, int pos, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  list_node *aux; 
  aux = li->head;
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

int list_find_mat(TLinkedList *li, int id, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  list_node *aux;
  aux = li->head;
  while(aux->data.id != id ){
    if (aux->next == NULL)
      return ELEM_NOT_FOUND;
    aux = aux->next;
  }
  *sl = aux->data;
  return SUCCESS;
}

int list_front(TLinkedList *li, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->head == NULL)
     return OUT_OF_RANGE;
  list_node *aux;
  aux = li->head;
  *sl = aux->data;  
  return SUCCESS;
}

int list_back(TLinkedList *li, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->head == NULL)
    return OUT_OF_RANGE;
  list_node *aux;
  aux = li->head;
  while(aux->next != NULL){
    aux = aux->next;
  }
  *sl = aux->data;
  return SUCCESS;
}

int list_get_pos(TLinkedList *li, int id, int *pos){
  if(li == NULL)
    return INVALID_NULL_POINTER;// lista não alocada
  int i = 1;
  *pos = i;
  list_node *aux; 
  aux = li->head;
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


int list_print(TLinkedList *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  list_node *aux = li->head;
  char Maxletra[10];
  printf("%s%*s%20s\n", "Id ",-MAXLETRAS, "Nome", "Notas");
  printf("------------------------------------------------\n"); 
  while(aux != NULL){
    printf("%d ",  aux->data.id);
    printf("%*s ",-MAXLETRAS, aux->data.name);
    printf("%15.1f %5.1f %5.1f\n",aux->data.g1,aux->data.g2,aux->data.g3); 
    printf("------------------------------------------------\n"); 
    aux = aux->next;
  }

return SUCCESS;
}