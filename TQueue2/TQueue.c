#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TQueue.h"
#define MAXLETRAS 10

struct TQueue{
  int front;
  int rear;
  int size;
  struct student data[MAX];
};

TQueue *create_queue(){
  TQueue *fi;
  fi = malloc (sizeof(struct TQueue));
  if (fi == NULL)
    return fi;
  fi->front = 0;
  fi->rear = 0;
  fi->size = 0;
  return fi;
}

int free_queue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  free(fi);
  return SUCCESS;
}

int enqueue(TQueue *fi, struct student sl){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  if(fi->size > 1 && fi->rear  == fi->front)
    return FULL;
  fi->data[fi->rear] = sl;
  fi->rear = (fi->rear+1)%MAX;
  fi->size++;
  return SUCCESS;
}


int dequeue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  if(fi->size == 0)
    return EMPTY;
  fi->front = (fi->front+1)%MAX;
  fi->size--;
  return SUCCESS;
}

int queue_front(TQueue *fi, struct student *sl){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  if(fi->size == 0)
    return EMPTY;
  *sl = fi->data[fi->front];
  return SUCCESS;
}

int queue_empty(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else{
    if(fi->size == 0)
      return EMPTY;
    else
      return NOT_EMPTY;
  }
}



int print_queue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  printf("%s%*s%20s\n", "Id ",-MAXLETRAS, "Nome", "Notas");
  printf("------------------------------------------------\n"); 
  if(fi->front < fi->rear){
    for (int i = fi->front; i < fi->rear; i++)  {
       printf("%d ",  fi->data[i].id);
      printf("%*s ",-MAXLETRAS, fi->data[i].name);
      printf("%15.1f %5.1f %5.1f\n",fi->data[i].g1, fi->data[i].g2, fi->data[i].g3); 
      printf("------------------------------------------------\n"); 
    }
  }
  if(fi->front > fi->rear || (fi->front == fi->rear && fi->size > 1)){
    for (int i = fi->front; i < MAX; i++)  {
      printf("%d ",  fi->data[i].id);
      printf("%*s ",-MAXLETRAS, fi->data[i].name);
      printf("%15.1f %5.1f %5.1f\n",fi->data[i].g1, fi->data[i].g2, fi->data[i].g3); 
      printf("------------------------------------------------\n"); 
    }

    for (int i = 0; i < fi->rear; i++)  {
      printf("%d ",  fi->data[i].id);
      printf("%*s ",-MAXLETRAS, fi->data[i].name);
      printf("%15.1f %5.1f %5.1f\n",fi->data[i].g1, fi->data[i].g2, fi->data[i].g3); 
      printf("------------------------------------------------\n"); 
    }
  }
  return SUCCESS;
}