To compile with full speed:
clang -O3 -DNDEBUG -I. main.c -o main

To plot the mandelbrot set:
clang -O3 -DNDEBUG -I. -lpng main.c benchmark/mandelbrot.c io/to_png.c -o main