#include <stdio.h>

#include "mpi.h"
#include "timer.h"

int main() {
    int n = 10000;

    vecd *v = vecd_new();
    timer *t = timer_new();
    timer_start(t);
    double x = 0.123456789123456789;
    for (int k = 0; k < n; k++) {
        int i = 0;
        while(i < vecd_size(v) && x > vecd_get(v, i)) {
            i++;
        }
        vecd_push_back(v, 0.0);
        for (int j = vecd_size(v) - 1; j > i; j--) {
            vecd_set(v, j, vecd_get(v, j - 1));
        }
        vecd_set(v, i, x);
        x = 4 * x * (1 - x);
    }
    timer_stop(t);
    vecd_delete(v);
    printf("Time for array: %e s\n", timer_time(t));
    timer_reset(t);

    listd *lst = listd_new();
    timer_start(t);  
    x = 0.123456789123456789;
    for (int k = 0; k < n; k++) {
        noded *no = listd_begin(lst);
        while  (no != listd_end(lst) && x > listd_value(no)) {
            no = listd_next(no);
        }
        listd_insert(lst, no, x);
        x = 4 * x * (1 - x);
    }
    timer_stop(t);
    listd_delete(lst);
    printf("Time for linked list: %e s\n", timer_time(t));  

    timer_delete(t);

    return 0;
}
