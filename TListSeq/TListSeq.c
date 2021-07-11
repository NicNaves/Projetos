#include <stdio.h>
#include <stdlib.h>
#include "TListSeq.h" 

struct list_seq{
int qtty;
struct student data[MAX];
};

List_seq* create_list_seq(){
  List_seq *list;
  list = (List_seq*) malloc(sizeof(struct list_seq));
  if(list != NULL)
    list->qtty = 0;
  return list; }

void free_list_seq(List_seq* list){
  free(list);
}

int consult_list_seq_pos(List_seq* list, int pos, struct student* sl){
  if(list == NULL)
    return UNALLOCATED;

  if (pos <= 0 || pos > list->qtty)
    return NEPOS;
  *sl = list->data[pos-1];
  return SUCCESS;
}

int consult_list_seq_id(List_seq* list, int id, struct student* sl){
  if(list == NULL)
    return UNALLOCATED;
  
  int i = 0;
  while(i<list->qtty && list->data[i].id != id)
    i++;
  if(i == list->qtty)
    return NOTFOUND;

  *sl = list->data[i];
  return SUCCESS;
}

int ins_list_seq_end(List_seq* list, struct student sl){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == MAX)
    return FULL;

  list->data[list->qtty] = sl;
  list->qtty++;
  return SUCCESS;
}

int ins_list_seq_fst(List_seq* list, struct student sl){
  if(list == NULL)
    return UNALLOCATED;

  if (list->qtty == MAX)
    return FULL;

  for (int i = list->qtty-1; i>=0; i--)
    list->data[i+1] = list->data[i];
  list->data[0] = sl;
  list -> qtty++;
  return SUCCESS;
}


int ins_list_seq_ord(List_seq* list, struct student sl){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == MAX)
    return FULL;
 
  struct student aux;// auxilar para andar com a lista
  for(int i = 0; i < list->qtty-1 ; i++){
    if(list->data[i+1].id < list->data[i].id){
      aux = list->data[i];
      list->data[i] = list->data[i+1];
      list->data[i+1] = aux;
    }
  }

  int i=0;
  while(i < list->qtty && list->data[i].id < sl.id){
  i++;
  }
  for(int c = list->qtty-1 ; c >= i; c--){
  list->data[c+1] = list->data[c];
  }
   list->data[i] = sl;
  list->qtty++;
return SUCCESS;
}

int rem_list_seq(List_seq* list, int id){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == 0)
    return EMPTY;

  int i = 0;
  while (i<list->qtty && list->data[i].id != id)
    i++;

  if(i == list->qtty)
    return NOTFOUND;
  
  for(int c=i; c<list->qtty-1; c++)
    list->data[c] = list->data[c+1];
  list->qtty--;
  return SUCCESS;
}

int rem_list_seq_fst(List_seq* list){
   if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == 0)
    return EMPTY;
  for(int c=0; c<list->qtty-1; c++)
    list->data[c] = list->data[c+1];
  list->qtty--;
  return SUCCESS;
}


int rem_list_seq_end(List_seq* list){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == 0)
    return EMPTY;

  list->qtty--;
  return SUCCESS;
}


int size_list_seq(List_seq* list){
  if(list == NULL)
    return UNALLOCATED;
  else
    return list->qtty;
}

int list_seq_full(List_seq* list){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == MAX)
    return SUCCESS;
  else 
    return NOT;
}

int list_seq_empty(List_seq* list){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == 0)
    return SUCCESS;
  else
    return NOT; 
  } 

int print_list_seq(List_seq* list){
  if(list == NULL)
    return UNALLOCATED;
  for(int i = 0; i<list->qtty; i++){
    printf("Matricula: %d\n", list->data[i].id);
    printf("Nome: %s\n", list->data[i].name);
    printf("Notas: %.2f %.2f %.2f\n", list->data[i].g1, list->data[i].g2, list->data[i].g3);
    printf("____________________________________________________________\n");
  }
  return SUCCESS;
}

int rem_list_seq_opt(List_seq* list, int id){
  if(list == NULL)
    return UNALLOCATED;
  if (list->qtty == 0)
    return EMPTY;
  int i=0;
  while(i<list->qtty && list->data[i].id != id)
    i++;
  if(i == list->qtty)
    return NOTFOUND;
  list->qtty--;
  list->data[i] = list->data[list->qtty];

  return SUCCESS;  
}