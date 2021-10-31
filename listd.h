#ifndef MPI_LISTD_H
#define MPI_LISTD_H

typedef struct Nodeld nodeld;
typedef struct Listd listd;

vecd *listd_new() ;
void listd_delete(listd *lst);

bool listd_empty(listd *lst)
int listd_size(listd *lst);
void listd_prepend(listd *lst, double x);
void listd_append(listd *lst, double x);
double listd_pop_left(listd *lst);
double listd_pop_right(listd *lst);

#endif //MPI_LISTD_H
