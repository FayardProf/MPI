#include "vectori.h"

#include <stdlib.h>
#include <assert.h>

struct vectori {
    int *data;
    int size;
    int capacity;
};

vectori *vectori_new() {
    vectori *v = malloc(sizeof(vectori));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vectori_delete(vectori *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

bool vectori_empty(vectori *v) {
    return v->size == 0;
}

int vectori_size(vectori *v) {
    return v->size;
}

void _vectori_increase_capacity(vectori* v, int r) {
    assert(v->capacity < r);
    int *new_data = malloc(r * sizeof(int));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

void vectori_resize(vectori* v, int n) {
    if (n > v->capacity) {
        _vectori_increase_capacity(v, n);
    }
    v->size = n;
}

void vectori_reserve(vectori* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _vectori_increase_capacity(v, r);
    }
}

int vectori_get(vectori *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

void vectori_set(vectori *v, int i, int x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

void vectori_swap(vectori *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    int x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

void vectori_push_back(vectori *v, int x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _vectori_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

int vectori_pop_back(vectori *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

int *vectori_data(vectori *v) {
    return v->data;
}