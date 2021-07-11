#ifndef TDLinkedListh
#define TDLinkedListh

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4

#include "../aluno.h"

typedef struct TDLinkedList TDLinkedList;


TDLinkedList* list_create();
int list_free(TDLinkedList* li);
int list_push_front(TDLinkedList *li, struct student al);
int list_push_back(TDLinkedList *li, struct student al);
int list_insert(TDLinkedList *li, int pos, struct student sl);
int list_size(TDLinkedList *li);
int list_pop_front(TDLinkedList *li);
int list_pop_back(TDLinkedList *li);
int list_erase(TDLinkedList *li, int pos);
int list_erase_mat(TDLinkedList *li, int id);
int list_find_mat(TDLinkedList *li, int id, struct student *sl);
int list_find_pos(TDLinkedList *li, int pos, struct student *sl);
int list_front(TDLinkedList *li, struct student *sl); 
int list_back(TDLinkedList *li, struct student *sl); 
int list_get_pos(TDLinkedList *li, int id, int *pos); 
int list_print_foward(TDLinkedList *li);
int list_print_reverse(TDLinkedList *li);

#endif
