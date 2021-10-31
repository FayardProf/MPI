#ifndef MPI_VECD_H
#define MPI_VECD_H

#include <stdbool.h>

typedef struct Vecd vecd;

vecd *vecd_new();
void vecd_delete(vecd *v);

bool vecd_empty(vecd *v);
int vecd_size(vecd *v);
void vecd_resize(vecd* v, int n);
void vecd_reserve(vecd* v, int r);
double vecd_get(vecd *v, int i);
void vecd_set(vecd *v, int i, double x);
void vecd_swap(vecd *v, int i, int j);
void vecd_push_back(vecd *v, double x);
double vecd_pop_back(vecd *v);

#endif //MPI_VECD_H
