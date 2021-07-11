#ifndef TQueueh
#define TQueueh

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define FULL -4
#define EMPTY -5
#define NOT_EMPTY -6

#include "../TLinkedList/TLinkedList.h"
#include "../aluno.h"


typedef struct TQueue TQueue;

TQueue* create_queue();
int free_queue(TQueue *fi);
int enqueue(TQueue *fi, struct student sl);
int dequeue(TQueue *fi);
int queue_front(TQueue *fi, struct student *sl);
int queue_empty(TQueue *fi);
int print_queue(TQueue *fi);


#endif