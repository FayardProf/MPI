#ifndef MPI_LISTD_H
#define MPI_LISTD_H

#include <stdbool.h>

typedef struct Noded noded;
typedef struct Listd listd;

listd *listd_new();
void listd_delete(listd *lst);

bool listd_empty(listd *lst);
int listd_size(listd *lst);
void listd_push_front(listd *lst, double x);
void listd_push_back(listd *lst, double x);
double listd_front(listd *lst);
double listd_back(listd *lst);
double listd_pop_front(listd *lst);
double listd_pop_back(listd *lst);
noded *listd_begin(listd *lst);
noded *listd_end(listd *lst);
noded *listd_next(noded *node);
double listd_value(noded *node);
void listd_insert(listd* lst, noded* node, double x);

#endif //MPI_LISTD_H
