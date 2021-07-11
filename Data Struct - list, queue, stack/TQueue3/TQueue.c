#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TQueue.h"
#define MAXLETRAS  10

struct TQueue{
  int front;
  int rear;
  int size;
  int MIN;
  int MAX;
  struct student *data;
};

TQueue *create_queue(int TAM){
  TQueue *fi;
  fi = malloc (sizeof(struct TQueue));
  if (fi == NULL)
    return fi;
  fi->front = 0;
  fi->rear = 0;
  fi->size = 0;
  fi->MIN = TAM;
  fi->MAX = TAM;
  fi->data = malloc(sizeof(struct student)*TAM);
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

  if(fi->size > 1 && (fi->rear == fi->front)){
    int prev;
    prev = fi->MAX;
    fi->MAX = fi->MAX + fi->MIN;
    struct student *new;
    new = realloc(fi->data,(sizeof(struct student)*fi->MAX));
    if(new == NULL){
      new = NULL;
      return OUT_OF_MEMORY;
    }
    fi->data = new ;
    for(int i = 0; i < fi->rear; i++){
      fi->data[prev] = fi->data[i];
      prev++;
    }
    fi->rear = fi->front + fi->size;
    fi->data[fi->rear] = sl;
    fi->rear = (fi->rear+1)%fi->MAX;
    fi->size++;
    return SUCCESS;
  }
  fi->data[fi->rear] = sl;
  fi->rear = (fi->rear+1)%fi->MAX;
  fi->size++;
  return SUCCESS;
}


int dequeue(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  if(fi->size == 0)
    return EMPTY;
  fi->front = (fi->front+1)%fi->MAX;
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
    for (int i = fi->front; i < fi->MAX; i++)  {
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

int size(TQueue *fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else
  return fi->size;
}

int suport_queue(TQueue* fi){
  if(fi == NULL)
    return INVALID_NULL_POINTER;
  else
    return fi->MAX;
}

TQueue* compact_queue(TQueue *fi){
float t = 1.0;
  int i = 1;
  t = fi->size;
  if(fi->size == 0)
    t = 1;
  i = ceil(t/fi->MIN)*fi->MIN;
  int count = 0;
  if(fi->front < fi->rear){
    while(count < fi->size){
      fi->data[count] = fi->data[fi->front];
      count++;
      fi->front++;
    }
    fi->front = 0;
    fi->rear = fi->size;
  }else if(fi->front > fi->rear){
      
    struct student temp[fi->size];
    while(fi->front < fi->MAX){
        temp[count] = fi->data[fi->front];
        count++;
        fi->front++;
    }
    int count2 = 0;
    while(count2 < fi->rear){
      temp[count] = fi->data[count2];
    }
    for(count = 0; count < fi->size; count++){
      fi->data[count] = temp[count];
    }
    fi->front = 0;
    fi->rear = fi->size;
  }
  fi->MAX = i;
  fi = realloc(fi,(sizeof(int)*5 + sizeof(struct student)*i));
    if(fi == NULL){
      free(fi);
      fi = NULL;
      return fi;
    }
 return fi;
}