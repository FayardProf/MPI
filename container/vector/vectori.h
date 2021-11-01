#ifndef MPI_VECTORI_H
#define MPI_VECTORI_H

#include <stdbool.h>

typedef struct vectori vectori;

vectori *vectori_new();
void vectori_delete(vectori *v);

bool vectori_empty(vectori *v);
int vectori_size(vectori *v);
void vectori_resize(vectori* v, int n);
void vectori_reserve(vectori* v, int r);
int vectori_get(vectori *v, int i);
void vectori_set(vectori *v, int i, int x);
void vectori_swap(vectori *v, int i, int j);
void vectori_push_back(vectori *v, int x);
int vectori_pop_back(vectori *v);
int *vectori_data(vectori *v);

#endif //MPI_VECTORI_H
