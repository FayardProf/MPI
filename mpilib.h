#ifndef MPILIB_MPILIB_H
#define MPILIB_MPILIB_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

typedef struct Timer timer;

struct Timer {
    double time;
    clock_t start_time;
};

static inline timer *timer_new() {
    timer *t = malloc(sizeof(timer));
		t->time = 0.0;
    return t;
}

static inline void timer_delete(timer *t) {
    free(t);
}

static inline void timer_start(timer *t) {
    t->start_time = clock();
}

static inline void timer_stop(timer *t) {
    clock_t stop_time = clock();
		t->time += (double) (stop_time - t->start_time) / CLOCKS_PER_SEC; 
}

static inline double timer_time(timer *t) {
    return t->time;
}

static inline void timer_reset(timer *t) {
    t->time = 0.0;
}

typedef struct Nodei nodei;
typedef struct Listi listi;

struct Nodei {
    int value;
    nodei *previous;
    nodei *next;
};

struct Listi {
    nodei *front;
    nodei *back;
};

static inline listi *listi_new() {
    listi *lst = malloc(sizeof(listi));
    lst->front = NULL;
    lst->back = NULL;
    return lst;    
}

static inline void listi_delete(listi *lst) {
    nodei *node = lst->front;
    while (node != NULL) {
        nodei *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

static inline bool listi_empty(listi *lst) {
    return lst->front == NULL;
}

static inline int listi_size(listi *lst) {
    int n = 0;
    nodei *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

static inline void listi_push_front(listi *lst, int x) {
    nodei *node = malloc(sizeof(nodei));
    node->value = x;
    node->previous = NULL;
    node->next = lst->front;
    if (listi_empty(lst)) {
        lst->back = node;
    } else {
        lst->front->previous = node;
    }
    lst->front = node;
}

static inline void listi_push_back(listi *lst, int x) {
    nodei *node = malloc(sizeof(nodei));
    node->value = x;
    node->previous = lst->back;
    node->next = NULL;
    if (listi_empty(lst)) {
        lst->front = node;
    } else {
        lst->back->next = node;
    }
    lst->back = node;
}

static inline int listi_front(listi *lst) {
    assert(!listi_empty(lst));
    return lst->front->value;
}

static inline int listi_back(listi *lst) {
    assert(!listi_empty(lst));
    return lst->back->value;
}

static inline int listi_pop_front(listi *lst) {
    assert(!listi_empty(lst));
    nodei* front = lst->front;
    int v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

static inline int listi_pop_back(listi *lst) {
    assert(!listi_empty(lst));
    nodei* back = lst->back;
    int v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

static inline nodei *listi_begin(listi *lst) {
    return lst->front;
}

static inline nodei *listi_end(listi *lst) {
    return NULL;
}

static inline nodei *listi_rbegin(listi *lst) {
    return lst->back;
}

static inline nodei *listi_rend(listi *lst) {
    return NULL;
}

static inline nodei *listi_next(nodei *no) {
	assert(no != NULL);
    return no->next;
}

static inline nodei *listi_previous(nodei *no) {
    assert(no != NULL);
    return no->previous;
}

static inline int listi_value(nodei *no) {
    assert(no != NULL);
    return no->value;
}

static inline void listi_insert(listi* lst, nodei* no, int x) {
    nodei *new_no = malloc(sizeof(nodei));
    new_no->value = x;
    new_no->next = no;
    if (no != NULL) {
        new_no->previous = no->previous;
        if (no->previous != NULL) {
            no->previous->next = new_no;
        }
        no->previous = new_no;
    } else {
        new_no->previous = lst->back;
        if (lst->back != NULL) {
            lst->back->next = new_no; 
        }
        lst->back = new_no;
    }
    if (new_no->previous == NULL) {
        lst->front = new_no;
    }
}

static inline void listi_erase(listi *lst, nodei *no) {
    assert(no != NULL);
    nodei *previous_no = no->previous;
    nodei *next_no = no->next;
    free(no);
    if (previous_no != NULL) {
        previous_no->next = next_no;
    } else {
        lst->front = next_no;
    }
    if (next_no != NULL) {
        next_no->previous = previous_no;
    } else {
        lst->back = previous_no;
    }
}

typedef struct Noded noded;
typedef struct Listd listd;

struct Noded {
    double value;
    noded *previous;
    noded *next;
};

struct Listd {
    noded *front;
    noded *back;
};

static inline listd *listd_new() {
    listd *lst = malloc(sizeof(listd));
    lst->front = NULL;
    lst->back = NULL;
    return lst;    
}

static inline void listd_delete(listd *lst) {
    noded *node = lst->front;
    while (node != NULL) {
        noded *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

static inline bool listd_empty(listd *lst) {
    return lst->front == NULL;
}

static inline int listd_size(listd *lst) {
    int n = 0;
    noded *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

static inline void listd_push_front(listd *lst, double x) {
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

static inline void listd_push_back(listd *lst, double x) {
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

static inline double listd_front(listd *lst) {
    assert(!listd_empty(lst));
    return lst->front->value;
}

static inline double listd_back(listd *lst) {
    assert(!listd_empty(lst));
    return lst->back->value;
}

static inline double listd_pop_front(listd *lst) {
    assert(!listd_empty(lst));
    noded* front = lst->front;
    double v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

static inline double listd_pop_back(listd *lst) {
    assert(!listd_empty(lst));
    noded* back = lst->back;
    double v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

static inline noded *listd_begin(listd *lst) {
    return lst->front;
}

static inline noded *listd_end(listd *lst) {
    return NULL;
}

static inline noded *listd_rbegin(listd *lst) {
    return lst->back;
}

static inline noded *listd_rend(listd *lst) {
    return NULL;
}

static inline noded *listd_next(noded *no) {
	assert(no != NULL);
    return no->next;
}

static inline noded *listd_previous(noded *no) {
    assert(no != NULL);
    return no->previous;
}

static inline double listd_value(noded *no) {
    assert(no != NULL);
    return no->value;
}

static inline void listd_insert(listd* lst, noded* no, double x) {
    noded *new_no = malloc(sizeof(noded));
    new_no->value = x;
    new_no->next = no;
    if (no != NULL) {
        new_no->previous = no->previous;
        if (no->previous != NULL) {
            no->previous->next = new_no;
        }
        no->previous = new_no;
    } else {
        new_no->previous = lst->back;
        if (lst->back != NULL) {
            lst->back->next = new_no; 
        }
        lst->back = new_no;
    }
    if (new_no->previous == NULL) {
        lst->front = new_no;
    }
}

static inline void listd_erase(listd *lst, noded *no) {
    assert(no != NULL);
    noded *previous_no = no->previous;
    noded *next_no = no->next;
    free(no);
    if (previous_no != NULL) {
        previous_no->next = next_no;
    } else {
        lst->front = next_no;
    }
    if (next_no != NULL) {
        next_no->previous = previous_no;
    } else {
        lst->back = previous_no;
    }
}

typedef struct vectori vectori;

struct vectori {
    int *data;
    int size;
    int capacity;
};

static inline vectori *vectori_new() {
    vectori *v = malloc(sizeof(vectori));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

static inline void vectori_delete(vectori *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

static inline bool vectori_empty(vectori *v) {
    return v->size == 0;
}

static inline int vectori_size(vectori *v) {
    return v->size;
}

static inline void _vectori_increase_capacity(vectori* v, int r) {
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

static inline void vectori_resize(vectori* v, int n) {
    if (n > v->capacity) {
        _vectori_increase_capacity(v, n);
    }
    v->size = n;
}

static inline void vectori_reserve(vectori* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _vectori_increase_capacity(v, r);
    }
}

static inline int vectori_get(vectori *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

static inline void vectori_set(vectori *v, int i, int x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

static inline void vectori_swap(vectori *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    int x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

static inline void vectori_push_back(vectori *v, int x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _vectori_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

static inline int vectori_pop_back(vectori *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

static inline int *vectori_data(vectori *v) {
    return v->data;
}


typedef struct vectord vectord;

struct vectord {
    double *data;
    int size;
    int capacity;
};

static inline vectord *vectord_new() {
    vectord *v = malloc(sizeof(vectord));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

static inline void vectord_delete(vectord *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

static inline bool vectord_empty(vectord *v) {
    return v->size == 0;
}

static inline int vectord_size(vectord *v) {
    return v->size;
}

static inline void _vectord_increase_capacity(vectord* v, int r) {
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

static inline void vectord_resize(vectord* v, int n) {
    if (n > v->capacity) {
        _vectord_increase_capacity(v, n);
    }
    v->size = n;
}

static inline void vectord_reserve(vectord* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _vectord_increase_capacity(v, r);
    }
}

static inline double vectord_get(vectord *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

static inline void vectord_set(vectord *v, int i, double x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

static inline void vectord_swap(vectord *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    double x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

static inline void vectord_push_back(vectord *v, double x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _vectord_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

static inline double vectord_pop_back(vectord *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

static inline double *vectord_data(vectord *v) {
    return v->data;
}

#endif //MPILIB_MPILIB_H