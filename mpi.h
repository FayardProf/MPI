#ifndef MPI_MPI_H
#define MPI_MPI_H

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct Vecd {
    double *data;
    int size;
    int capacity;
};

typedef struct Vecd vecd;

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

double *vecd_data(vecd *v) {
    return v->data;
}

typedef struct Noded noded;

struct Noded {
    double value;
    noded *previous;
    noded *next;
};

typedef struct Listd listd;

struct Listd {
    noded *front;
    noded *back;
};

listd *listd_new() {
    listd *lst = malloc(sizeof(listd));
    lst->front = NULL;
    lst->back = NULL;
    return lst;
}

void listd_delete(listd *lst) {
    noded *node = lst->front;
    while (node != NULL) {
        noded *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

bool listd_empty(listd *lst) {
    return lst->front == NULL;
}

int listd_size(listd *lst) {
    int n = 0;
    noded *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

void listd_push_front(listd *lst, double x) {
    noded *node = malloc(sizeof(noded));
    node->value = x;
    node->previous = NULL;
    node->next = lst->front;
    if (listd_empty(lst)) {
        lst->back = node;
    } else {
        lst->front->previous = node;
    }
    lst->front = node;
}

void listd_push_back(listd *lst, double x) {
    noded *node = malloc(sizeof(noded));
    node->value = x;
    node->previous = lst->back;
    node->next = NULL;
    if (listd_empty(lst)) {
        lst->front = node;
    } else {
        lst->back->next = node;
    }
    lst->back = node;
}

double listd_front(listd *lst) {
    assert(!listd_empty(lst));
    return lst->front->value;
}

double listd_back(listd *lst) {
    assert(!listd_empty(lst));
    return lst->back->value;
}

double listd_pop_front(listd *lst) {
    assert(!listd_empty(lst));
    noded* front = lst->front;
    double v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

double listd_pop_back(listd *lst) {
    assert(!listd_empty(lst));
    noded* back = lst->back;
    double v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

noded *listd_begin(listd *lst) {
    return lst->front;
}

noded *listd_end(listd *lst) {
    return NULL;
}

noded *listd_next(noded *node) {
    return node->next;
}

double listd_value(noded *node) {
    return node->value;
}

void listd_insert(listd* lst, noded* node, double x) {
    noded *new_node = malloc(sizeof(noded));
    new_node->value = x;
    new_node->next = node;
    if (node != NULL) {
        new_node->previous = node->previous;
        if (node->previous != NULL) {
            node->previous->next = new_node;
        }
        node->previous = new_node;
    } else {
        new_node->previous = lst->back;
        if (lst->back != NULL) {
            lst->back->next = new_node; 
        }
        lst->back = new_node;
    }
    if (new_node->previous == NULL) {
        lst->front = new_node;
    }
}

#endif //MPI_MPI_H