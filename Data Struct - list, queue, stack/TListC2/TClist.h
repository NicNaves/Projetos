#ifndef TLinkedListh
#define TLinkedListh

#define SUCCESS 0
#define INVALID_NULL_POINTER -1
#define OUT_OF_MEMORY -2
#define OUT_OF_RANGE -3
#define ELEM_NOT_FOUND -4
#define SORTED -5;


#include "..\aluno.h"

typedef struct TClist TClist;

TClist* list_create(int ord);
int list_free(TClist *li);
int list_push_front(TClist *li, struct student sl);
int list_push_back(TClist *li, struct student sl);
int list_size(TClist *li);
int list_pop_front(TClist *li);
int list_pop_back(TClist *li);
int list_insert(TClist *li, int pos, struct student sl);
int list_insert_sorted(TClist *li, struct student sl);
int list_erase_mat(TClist *li, int pos);
int list_erase_pos(TClist *li, int pos);
int list_find_pos(TClist *li, int pos, struct student *sl);
int list_find_mat(TClist *li, int id, struct student *sl);
int list_front(TClist *li, struct student *sl);
int list_back(TClist *li, struct student *sl);
int list_get_pos(TClist *li, int id, int *pos);
int list_get_next (TClist *li, struct student *next);
int list_print(TClist *li);

#endif