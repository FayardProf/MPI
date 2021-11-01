#include <stdio.h>

#include "mpilib.h"

void vector_vs_list(int n) {
    printf("Size: %d\n", n);
    timer *t = timer_new();

    vectord *v = vectord_new();
    timer_start(t);
    double x = 0.123456789123456789;
    for (int k = 0; k < n; k++) {
        int i = 0;
        while(i < vectord_size(v) && x > vectord_get(v, i)) {
            i++;
        }
        vectord_push_back(v, 0.0);
        for (int j = vectord_size(v) - 1; j > i; j--) {
            vectord_set(v, j, vectord_get(v, j - 1));
        }
        vectord_set(v, i, x);
        x = 4 * x * (1 - x);
    }
    timer_stop(t);
    vectord_delete(v);
    double time_array = timer_time(t);
    printf("Time for dynamic array: %e s\n", time_array);
    timer_reset(t);

    listd *lst = listd_new();
    timer_start(t);  
    x = 0.123456789123456789;
    for (int k = 0; k < n; k++) {
        noded *no = listd_begin(lst);
        while (no != listd_end(lst) && x > listd_value(no)) {
            no = listd_next(no);
        }
        listd_insert(lst, no, x);
        x = 4 * x * (1 - x);
    }
    timer_stop(t);
    listd_delete(lst);
    double time_list = timer_time(t);
    printf("Time for linked list: %e s\n", time_list);  
    printf("Speedup of array over list: %f\n", time_list / time_array);
    timer_delete(t);
}
