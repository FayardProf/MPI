#ifndef MPI_VECTORD_H
#define MPI_VECTORD_H

#include <stdbool.h>

typedef struct vectord vectord;

vectord *vectord_new();
void vectord_delete(vectord *v);

bool vectord_empty(vectord *v);
int vectord_size(vectord *v);
void vectord_resize(vectord* v, int n);
void vectord_reserve(vectord* v, int r);
double vectord_get(vectord *v, int i);
void vectord_set(vectord *v, int i, double x);
void vectord_swap(vectord *v, int i, int j);
void vectord_push_back(vectord *v, double x);
double vectord_pop_back(vectord *v);
double *vectord_data(vectord *v);

#endif //MPI_VECTORD_H
