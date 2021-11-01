#include "matrixui8.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

struct Matrixui8 {
    uint8_t *data;
    int size[2];
    int capacity[2];
};

matrixui8 *matrixui8_new() {
    matrixui8 *m = malloc(sizeof(matrixui8));
    m->data = NULL;
    m->size[0] = 0;
	m->size[1] = 0;
	m->capacity[0] = 0;
    m->capacity[1] = 0;
    return m;
}

void matrixui8_delete(matrixui8 *m) {
    if (m->data != NULL) {
        free(m->data);
    }
    free(m);
}

int matrixui8_size(matrixui8 *m, int d) {
    assert(d == 0 || d == 1);
    return m->size[d];
}

int matrixui8_capacity(matrixui8 *m, int d) {
    assert(d == 0 || d == 1);
    return m->capacity[d];  
}

void matrixui8_resize(matrixui8 *m, int n0, int n1) {
    assert(n0 >= 0);
    assert(n1 >= 0);
    int n0_capacity = matrixui8_capacity(m, 0);
    int n1_capacity = matrixui8_capacity(m, 1);
    if (n0 > n0_capacity || n1 > n1_capacity) {
        int n0_old = matrixui8_size(m, 0);
        int n1_old = matrixui8_size(m, 1);
        uint8_t *new_data = malloc(n0 * n1 * sizeof(uint8_t));
        if (m->data != NULL) {
            for (int i0 = 0; i0 < n0_old; i0++) {
                for (int i1 = 0; i1 < n1_old; i1++) {
                    new_data[i0 * n1 + i1] = m->data[i0 * m->capacity[1] + i1];
                }
            }
        }
        m->capacity[0] = n0;
        m->capacity[1] = n1;
        m->data = new_data;
    }
    m->size[0] = n0;
    m->size[1] = n1;
}

int8_t matrixui8_get(matrixui8 *m, int i0, int i1) {
    return m->data[i0 * m->capacity[1] + i1];
}

void matrixui8_set(matrixui8 *m, int i0, int i1, int8_t x) {
    assert(i0 >= 0 && i0 < m->capacity[0]);
    assert(i1 >= 0 && i1 < m->capacity[1]);
    m->data[i0 * m->capacity[1] + i1] = x;
}

