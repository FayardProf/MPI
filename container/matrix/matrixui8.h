#ifndef MPI_MATRIXUI8_H
#define MPI_MATRIXUI8_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Matrixui8 matrixui8;

matrixui8 *matrixui8_new();
void matrixui8_delete(matrixui8 *m);

bool matrixui8_empty(matrixui8 *m);
int matrixui8_size(matrixui8 *m, int d);
int matrixui8_capacity(matrixui8 *m, int d);
void matrixui8_resize(matrixui8 *m, int n0, int n1);
void matrixui8_reserve(matrixui8 *m, int r0, int r1);
int8_t matrixui8_get(matrixui8 *m, int i0, int i1);
void matrixui8_set(matrixui8 *m, int i0, int i1, int8_t x);
int8_t *matrixui8_data(matrixui8 *m);

#endif //MPI_MATRIXUI8_H