#include "listd.h"

#include <stdlib.h>
#include <assert.h>

struct Nodeld_t {
    double value;
    listd *previous;
    listd *next;
};

struct Listd_t {
    nodeld *first;
		nodeld *last;
		int size;
}

listd *listd_new() {
    listd *lst = malloc(sizeof(listd));
    lst->first = NULL;
    lst->last = NULL;
    lst->size = 0;
    return v;
}

void listd_delete(listd *lst) {
    nodeld *node = lst->first;
		while (node != NULL) {
        nodeld *next_node = node->next;
				free(node);
				node = next_node;
		}
		free(lst);
}
