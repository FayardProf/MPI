#include "listd.h"

#include <stdlib.h>
#include <assert.h>

struct Nodeld {
    double value;
    nodeld *previous;
    nodeld *next;
};

struct Listd {
    nodeld *front;
		nodeld *back;
};

listd *listd_new() {
    listd *lst = malloc(sizeof(listd));
    lst->front = NULL;
    lst->back = NULL;
    return lst;
}

bool listd_empty(listd *lst) {
    return lst->front == NULL;
}

int listd_size(listd *lst) {
    int n = 0;
    nodeld *node = lst->front;
    while (node != NULL) {
        node = node->next;
				n++;
    }
    return n;
}

void listd_delete(listd *lst) {
    nodeld *node = lst->front;
    while (node != NULL) {
        nodeld *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

void listd_push_front(listd *lst, double x) {
    nodeld *node = malloc(sizeof(nodeld));
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
    nodeld *node = malloc(sizeof(nodeld));
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
    nodeld* front = lst->front;
    double v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

double listd_pop_back(listd *lst) {
    assert(!listd_empty(lst));
    nodeld* back = lst->back;
    double v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}