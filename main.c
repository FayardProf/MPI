#include <stdio.h>

#include "vecd.h"
#include "listd.h"

int main() {
    int n = 5;

    vecd *v = vecd_new();
    for (int i = 0; i < n; i++) {
        vecd_push_back(v, 1.0);
    }
    printf("Size: %d\n", vecd_size(v));
    vecd_delete(v);

    listd *lst = listd_new();
    for (int i = 0; i < n; i++) {
        listd_push_back(lst, 1.0);
    }	
    printf("Size: %d\n", listd_size(lst));
    listd_delete(lst);

    return 0;
}
