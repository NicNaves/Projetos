
#include "TClist.h"
#include <stdlib.h>
#include<stdio.h>
#define MAXLETRAS  10

typedef struct Clist_node Clist_node;

// node definition
struct Clist_node {
    struct student data;
    Clist_node *next;
};

// list definition
struct TClist {
    Clist_node *end;
    Clist_node *next;
    int size;
    int sorted;
};

// list_create - cria a lista, fazendo as alocações necessária
TClist* list_create(int ord){
    TClist *list;
    list = malloc(sizeof(TClist));
    if (list != NULL){
        list->end = NULL;
        list->size = 0;
        list->next = NULL;
        if (ord == 0 || ord == 1)
          list->sorted = ord;
        else
          return NULL;
    }
    return list;
};

// list_free - libera toda a lista da memória
int list_free(TClist *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  Clist_node *aux = li->end->next;
  Clist_node *previous = NULL;
  while(aux != NULL){
    previous = aux;
    aux = aux->next;
    free(previous);
  }
  free(li);
  return SUCCESS;
}

/// list_push_front - insere no inicio
int list_push_front(TClist *li, struct student sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->sorted == 1)
    return SORTED;
  Clist_node *new_node = malloc(sizeof(struct Clist_node));
  if(new_node == NULL)
    return INVALID_NULL_POINTER;
  if (li->end == NULL){ // caso a lista esteja vazia
    new_node->data = sl;
    li->end = new_node;
    li->end->next = new_node;
  }
  new_node->data = sl; 
  new_node->next = li->end->next;
  li->end->next = new_node;
  li->size++;
  return SUCCESS;
}

int list_push_back(TClist *li, struct student sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  Clist_node *new_node = malloc(sizeof(struct Clist_node));
  if(new_node == NULL)
    return INVALID_NULL_POINTER;
  if (li->sorted == 1)
    return SORTED;
  if (li->end == NULL){ // caso a lista esteja vazia
    new_node->data = sl;
    li->end = new_node;
    li->end->next = new_node;
  }
  new_node->data = sl; 
  new_node->next = li->end->next;
  li->end->next = new_node;
  li->end = new_node;
  li->size++;
  return SUCCESS;

}

int list_insert(TClist *li, int pos, struct student sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  Clist_node *new_node = malloc(sizeof(Clist_node));
  if(new_node == NULL)
    return INVALID_NULL_POINTER;
  if(li->sorted == 1)
    return SORTED;
  new_node->data = sl;
  new_node->next = NULL;

int x = 1;
  Clist_node *aux = li->end->next;
  Clist_node *previous = li->end;
  if(pos == 1){
      new_node->next = li->end->next;
      li->end->next = new_node;
      li->size++;
      return SUCCESS;
    }
  else if (pos > li->size){
      new_node->next = li->end->next;
      previous->next = new_node;
      li->end = new_node;
      li->size++;
      return SUCCESS;
    }
  else{
    while(x < pos){
      previous = aux;
      aux = aux->next;
      x++;
      }
      if (aux == NULL)
        return OUT_OF_MEMORY;
      new_node->next = aux;
      previous->next = new_node;
  }
  li->size++;
  return SUCCESS;
}

int list_insert_sorted(TClist *li, struct student sl){
  if (li == NULL){
    return INVALID_NULL_POINTER;
  }else {
    Clist_node *node;
    node = malloc(sizeof(Clist_node));
    if (node == NULL)
      return OUT_OF_MEMORY;
    else{
      node->data = sl;
      if (li->end == NULL){
        node->next = node;
        li->end = node;
      } else {
        Clist_node *aux, *previous;
        aux = li->end->next;
        if(sl.id < aux->data.id){
          node->next = li->end->next;
          li->end->next = node;
        } else {
        while (aux->data.id < sl.id && aux != li->end) {
          previous = aux;
          aux = aux->next;
        }
        if (aux == li->end) {
          node->next = li->end->next;
          aux->next = node;
          li->end = node;
        } else {
          previous->next = node;
          node->next = aux;
        }
       }
      }
      li->size++;
      return SUCCESS;
    }
  }
}


int list_size(TClist *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  Clist_node *aux = li->end->next;
  if(aux == NULL)
    return OUT_OF_RANGE;
  int size = 0;
  while(aux != li->end){
    aux = aux->next;
    size++;
  }
  size++;

  return size;
}


int list_pop_front(TClist *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  Clist_node *aux = li->end->next;
  if (li->next == aux)
    li->next = aux->next;
  li->end->next = aux->next;
  li->size--;
  free(aux);
  return SUCCESS;
}

int list_pop_back(TClist *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  if(li->end->next == li->end){
    free(li->end);
    li->end = NULL;
    li->size--;
    return SUCCESS;
  }
  if (li->next == li->end)
    li->next = li->end->next;
  Clist_node *previous = NULL;
  Clist_node *aux = li->end;
  while(aux->next != li->end){
    previous = aux;
    aux = aux->next;
  }
  previous = aux;
  aux = aux->next;
  previous->next = li->end->next;
  li->end = previous;
  li->size--;
  free(aux);
return SUCCESS;
}



int list_erase_mat(TClist *li, int id){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  Clist_node *previous = li->end;
  Clist_node *aux = li->end->next;
  int pos = 1;
  while (aux != NULL &&  aux->data.id != id){
    previous = aux;
    aux = aux->next;
    pos++;
  }
  if(aux == NULL)
    return ELEM_NOT_FOUND;
  if(li->next == aux)
    li->next = aux->next;
  previous->next = aux->next;
  li->size--;
  if(aux == li->end)
  li->end = previous;
  free(aux);
  return SUCCESS;
}

int list_erase_pos(TClist *li, int pos){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL){
    return OUT_OF_MEMORY;
  }
  Clist_node *previous = li->end;
  Clist_node *aux = li->end->next;
  int x=1;
  while (aux != NULL &&  x != pos){
    previous = aux;
    aux = aux->next;
    x++;
  }
  if(aux == NULL)
    return ELEM_NOT_FOUND;
  if(li->next == aux)
    li->next = aux->next;
  previous->next = aux->next;
  li->size--;
  if(aux == li->end)
  li->end = previous;
  if(aux == li->end->next)
  li->end->next = aux->next;
  free(aux);
return SUCCESS;
}


int list_find_pos(TClist *li, int pos, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  int x=1;
  Clist_node *aux;
  aux = li->end->next;
    while (aux != NULL &&  x != pos){
    aux = aux->next;
    x++;
    }
    if(aux == NULL)
      return ELEM_NOT_FOUND;
    *sl = aux->data;
  return SUCCESS;
}

int list_find_mat(TClist *li, int id, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  Clist_node *aux;
  aux = li->end->next;
  int x = 0;
  while (aux->data.id != id && (x != ((li->size)+1))){ // +1 para não entrar em loop
  aux = aux->next;
  x++;
  }
  if(aux == NULL || x == ((li->size)+1)){ //+1 para não entrar em loop
    return ELEM_NOT_FOUND;
  } else {
  *sl = aux->data;
  }
  return SUCCESS;
}

int list_front(TClist *li, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  Clist_node *aux;
  aux = li->end->next;
  *sl = aux->data;
  return SUCCESS;
}

int list_back(TClist *li, struct student *sl){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  Clist_node *aux;
  aux = li->end;
  *sl = aux->data;
  return SUCCESS;
}


int list_get_pos(TClist *li, int id, int *pos){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  Clist_node *aux;
  aux = li->end->next;
  int x=1;
  while (x != ((li->size)+5) &&  aux->data.id != id){
  aux = aux->next;
  x++;
  }
  if(aux == NULL || x == ((li->size)+5))
    return OUT_OF_RANGE;
  *pos = x;
  return SUCCESS;
}

int list_get_next (TClist *li, struct student *next){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  if(li->end == NULL)
    return OUT_OF_MEMORY;
  if(li->next == NULL)
    li->next = li->end->next;
  *next = li->next->data;
  li->next = li->next->next;
  return SUCCESS;
}


int list_print(TClist *li){
  if(li == NULL)
    return INVALID_NULL_POINTER;
  Clist_node *aux = li->end->next;
  char Maxletra[10];
  printf("%s%*s%20s\n", "Id ",-MAXLETRAS, "Nome", "Notas");
  printf("------------------------------------------------\n"); 
  while(aux != li->end){
    printf("%d ",  aux->data.id);
    printf("%*s ",-MAXLETRAS, aux->data.name);
    printf("%15.1f %5.1f %5.1f\n",aux->data.g1,aux->data.g2,aux->data.g3); 
    printf("------------------------------------------------\n"); 
    aux = aux->next;
  }
  printf("%d ",  aux->data.id);
  printf("%*s ",-MAXLETRAS, aux->data.name);
  printf("%15.1f %5.1f %5.1f\n",aux->data.g1,aux->data.g2,aux->data.g3); 
  printf("------------------------------------------------\n"); 

return SUCCESS;
}