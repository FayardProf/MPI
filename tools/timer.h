#ifndef MPI_TIMER_H
#define MPI_TIMER_H

#include <stdbool.h>

typedef struct Timer timer;

timer *timer_new();
void timer_delete(timer *t);

void timer_start(timer *t);
void timer_stop(timer *t);
void timer_reset(timer *t);
double timer_time(timer *t);
void timer_reset(timer *t);

#endif //MPI_TIMER_H
