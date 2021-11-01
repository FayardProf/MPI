#ifndef MPI_MATRIXD_H
#define MPI_MATRIXD_H

#include <stdbool.h>

typedef struct Matrixd matrixd;

matrixd *matrixd_new();
void matrixd_delete(matrixd *m);

bool matrixd_empty(matrixd *m);
int matrixd_size(matrixd *m);
void matrixd_resize(matrixd *m, int n0, int n1);
void matrixd_reserve(matrixd *m, int r0, int r1);
double matrixd_get(matrixd *m, int i0, int i1);
void matrixd_set(matrixd *m, int i0, int i1, double x);
double *matrixd_data(matrixd *m);

#endif //MPI_MATRIXD_H