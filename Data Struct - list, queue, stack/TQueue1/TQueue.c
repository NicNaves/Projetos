#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TQueue.h"
#include "../TLinkedList/TLinkedList.h"

struct TQueue{
  TLinkedList* data;
};

TQueue *create_queue(){
  TQueue *fi;
  fi = malloc(sizeof(TQueue));
    if(fi == NULL)
      return fi;
    fi->data = list_create();
    if(fi->data == NULL){
      free(fi);
      fi = NULL;
    }
    return fi;
}


int free_queue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else{
    list_free(fi->data);
    free(fi);
    return SUCCESS;
  }
}

int enqueue(TQueue *fi, struct student sl){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else
    return (list_push_back(fi->data, sl));
}

int print_queue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else
    return (list_print(fi->data));
}

int dequeue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else
    return (list_pop_front(fi->data));
}

int queue_front(TQueue *fi, struct student *sl){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else
    return (list_front(fi->data, sl));
}

int queue_empty(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else{
    if(list_size(fi->data) == 0)
      return EMPTY;
    else
      return NOT_EMPTY;
  }
}
