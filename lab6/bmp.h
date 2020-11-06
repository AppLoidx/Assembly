#ifndef _BMP_H___
#define _BMP_H___
#include <stdint.h>
#include <stdio.h>

#include "bmp_struct.h"

#define MAGIC 0x4d42

enum Error
{
    OK,
    FILE_ERR,
    TYPE_ERR,
    BITCOUNT_ERR
};

struct source *parse_image(FILE *image, uint32_t width, uint32_t height);
enum Error read_header(FILE *image, struct bmp_header *header);
struct image *read_image(FILE *image);
struct image *rotate(struct image *image);
struct source *rotate_image(struct source *image);
struct bmp_header rotate_header(struct bmp_header header);
void write_image(struct source *img, struct bmp_header *header, FILE *image);
void check_h(struct bmp_header h);
#endif
