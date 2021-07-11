#ifndef TLinkedListSortedh
#define TLinkedListSortedh

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define SORTED -5




#include "..\aluno.h"

typedef struct TLinkedList TLinkedList;

TLinkedList* list_create(int x);
int list_free(TLinkedList *li);

int list_push_front(TLinkedList *li, struct student sl);
int list_push_back(TLinkedList *li, struct student sl);
int list_insert(TLinkedList *li, int pos, struct student sl);

int list_insert_sorted(TLinkedList *li, struct student sl);

int list_size(TLinkedList *li);


int list_pop_front(TLinkedList *li);
int list_pop_back(TLinkedList *li);
int list_erase(TLinkedList *li, int pos);

int list_find_pos(TLinkedList *li, int pos, struct student *sl);
int list_find_mat(TLinkedList *li, int nmat, struct student *sl);
int list_front(TLinkedList *li, struct student *sl);
int list_back(TLinkedList *li, struct student *sl);
int list_get_pos(TLinkedList *li, int id, int *pos);

int list_print(TLinkedList *li);

#endif