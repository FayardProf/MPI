#include <stdio.h>

#include "mpilib.h"
#include "benchmark/mandelbrot.h"
#include "io/to_png.h"


int main() {
    float x_left = -1.5;
    float x_right = 0.5;
    float y_bottom = -1.0;
    float y_top = 1.0;
    int depth = 255;
    int nx = 4000;
    int ny = 4000;
    matrixui8 *m = mandelbrot(x_left, x_right, y_bottom, y_top, depth, nx, ny);
    save_matrixui8_to_png(m, "mandelbrot.png");

    return 0;
}
