#include "vecd.h"

#include <stdlib.h>
#include <assert.h>

struct Vecd {
    double *data;
    int size;
    int capacity;
};

vecd *vecd_new() {
    vecd *v = malloc(sizeof(vecd));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vecd_delete(vecd *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

bool vecd_empty(vecd *v) {
    return v->size == 0;
}

int vecd_size(vecd *v) {
    return v->size;
}

void _vecd_increase_capacity(vecd* v, int r) {
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

void vecd_resize(vecd* v, int n) {
    if (n > v->capacity) {
        _vecd_increase_capacity(v, n);
    }
    v->size = n;
}

void vecd_reserve(vecd* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _vecd_increase_capacity(v, r);
    }
}

double vecd_get(vecd *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

void vecd_set(vecd *v, int i, double x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

void vecd_swap(vecd *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    double x = v->data[i];
		v->data[i] = v->data[j];
		v->data[j] = x;
}

void vecd_push_back(vecd *v, double x) {
    int n = v->size;
		int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
				_vecd_increase_capacity(v, new_r);
    }
		v->data[n] = x;
    v->size++;
}

double vecd_pop_back(vecd *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}