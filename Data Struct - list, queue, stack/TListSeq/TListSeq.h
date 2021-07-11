#ifndef TListSeqh
#define TListSeqh


#define MAX 100
#define SUCCESS 0
#define UNALLOCATED -1
#define FULL -2
#define NEPOS -3
#define NOTFOUND -4
#define EMPTY -5
#define NOT -6

#include "../aluno.h"
typedef struct list_seq List_seq;

List_seq* create_list_seq();
void free_list_seq(List_seq* list);
int consult_list_seq_pos(List_seq* list, int pos, struct student* sl);
int consult_list_seq_id(List_seq* list, int id, struct student* sl);
int ins_list_seq_end(List_seq* list, struct student sl);
int ins_list_seq_fst(List_seq* list, struct student sl);
int ins_list_seq_ord(List_seq* list, struct student sl);
int rem_list_seq(List_seq* list, int id);
int rem_list_seq_fst(List_seq* list);
int rem_list_seq_end(List_seq* list);
int size_list_seq(List_seq* list);
int list_seq_full(List_seq* list);
int list_seq_empty(List_seq* list);
int print_list_seq(List_seq* list);
int rem_list_seq_opt(List_seq* list, int id);

#endif