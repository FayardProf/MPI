#include "vectord.h"

#include <stdlib.h>
#include <assert.h>

struct vectord {
    double *data;
    int size;
    int capacity;
};

vectord *vectord_new() {
    vectord *v = malloc(sizeof(vectord));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vectord_delete(vectord *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

bool vectord_empty(vectord *v) {
    return v->size == 0;
}

int vectord_size(vectord *v) {
    return v->size;
}

void _vectord_increase_capacity(vectord* v, int r) {
    assert(v->capacity < r);
    double *new_data = malloc(r * sizeof(double));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

void vectord_resize(vectord* v, int n) {
    if (n > v->capacity) {
        _vectord_increase_capacity(v, n);
    }
    v->size = n;
}

void vectord_reserve(vectord* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _vectord_increase_capacity(v, r);
    }
}

double vectord_get(vectord *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

void vectord_set(vectord *v, int i, double x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

void vectord_swap(vectord *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    double x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

void vectord_push_back(vectord *v, double x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _vectord_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

double vectord_pop_back(vectord *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

double *vectord_data(vectord *v) {
    return v->data;
}