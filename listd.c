#include "listd.h"

#include <stdlib.h>
#include <assert.h>

struct Noded {
    double value;
    noded *previous;
    noded *next;
};

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