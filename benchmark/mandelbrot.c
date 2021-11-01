#include "mpilib.h"
#include "png.h"

void savepng(matrixui8 *m, const char *file) {
    FILE *fp = fopen(file, "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_uint_32 width = matrixui8_size(m, 1);
    png_uint_32 height = matrixui8_size(m, 0);
    int bit_depth = 8;
    int color_type = 2;
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    png_bytep *row_pointers = malloc(height * sizeof(png_bytep));
    for (int ky = 0; ky < matrixui8_size(m, 0); ky++) {
        row_pointers[ky] = malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    for (int ky = 0; ky < matrixui8_size(m, 0); ky++) {
        png_bytep row = row_pointers[ky];
        for (int kx = 0; kx < matrixui8_size(m, 1); kx++) {
            for (int kc = 0; kc < 2; kc++) {
                row[3 * kx + kc] = matrixui8_get(m, ky, kx);
            }
        }
    }
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);
    for (int ky = 0; ky < matrixui8_size(m, 0); ky++) {
        free(row_pointers[ky]);
    }
    free(row_pointers);
}

matrixui8 *mandelbrot(float x_left, float x_right, float y_bottom, float y_top, int depth, int nx, int ny) {
    float dx = (x_right - x_left) / nx;
    float dy = (y_top - y_bottom) / ny;
    matrixui8 *m = matrixui8_new();
    matrixui8_resize(m, ny, nx);
    for (int ky = 0; ky < ny; ky++) {
        float y = y_top - ky * dy;
        for (int kx = 0; kx < nx; kx++) {
            float x = x_left + kx * dx;
            float z_re = 0.0;
            float z_im = 0.0;
            int count = 0;
            while (count < depth) {
                if (z_re * z_re + z_im * z_im > 4.0) {
                    break;
                }
                float old_z_re = z_re;
                z_re = z_re * z_re - z_im * z_im + x;
                z_im = 2 * old_z_re * z_im + y;
                ++count;
            }
            matrixui8_set(m, ky, kx, (uint8_t) (255 * (((float) count) / depth)));
        }
    }
    return m;
}