#include "bmp.h"
#include "bmp_struct.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void *memcpy(void *dest, const void *src, size_t len)
{
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}

void write_image(struct source *img, struct bmp_header *header, FILE *image)
{

    fwrite(header, sizeof(struct bmp_header), 1, image);
    uint8_t padding = (4 - (img->width * sizeof(struct pixel)) % 4) % 4;
    for (uint32_t count = 0; count < img->height; count++)
    {
        fwrite(img->pixels + (count * img->width), sizeof(struct pixel), img->width, image);
        fwrite(&padding, 1, padding, image);
    }
}

enum Error read_header(FILE *image, struct bmp_header *header)
{
    if (image == NULL)
    {
        return FILE_ERR;
    }

    fread(header, sizeof(struct bmp_header), 1, image);

    if (header->bfType != MAGIC)
    {
        return TYPE_ERR;
    }
    else if (header->biBitCount != 24)
    {
        return BITCOUNT_ERR;
    }
    return OK;
}

struct source *rotate_image(struct source *origin)
{
    struct source *new_image = malloc(sizeof(struct source));
    new_image->height = origin->width;
    new_image->width = origin->height;
    new_image->pixels = (struct pixel *)malloc(new_image->width * sizeof(struct pixel) * new_image->height);

    for (uint32_t i = 0; i < new_image->height; i++)
    {
        for (uint32_t j = 0; j < new_image->width; j++)
        {
            *(new_image->pixels + i * new_image->width + j) = *(origin->pixels + j * origin->width + (origin->width - 1 - i));
        }
    }
    return new_image;
}

struct bmp_header *rotate_h(struct bmp_header *header)
{
    struct bmp_header *new_header = malloc(sizeof(struct bmp_header));

    char *d = (void *)new_header;
    const char *s = (void *)header;
    size_t len = sizeof(struct bmp_header);
    while (len--)
        *d++ = *s++;

    new_header->biWidth = header->biHeight;
    new_header->biHeight = header->biWidth;

    return new_header;
}

struct source *parse_image(FILE *image, uint32_t width, uint32_t height)
{
    struct source *img = malloc(sizeof(struct image));
	img->height = height;
	img->width = width;
	img->pixels = (struct pixel*)malloc(img->width*sizeof(struct pixel)*img->height);
	uint8_t padding = (4 - (img->width * sizeof(struct pixel)) % 4) % 4;
	for (uint32_t count = 0; count < img->height; count++) {
		fread(img->pixels+(count*img->width), sizeof(struct pixel), img->width, image);
		fseek(image, padding, SEEK_CUR);
	}
	return img;

}

struct image *read_image(FILE *image_f)
{
    struct image *origin_image = malloc(sizeof(struct image));
    origin_image->header = malloc(sizeof(struct bmp_header));
    enum Error status = read_header(image_f, origin_image->header);
    if (status != OK)
    {
        exit(1);
    }

    fseek(image_f, origin_image->header->bOffBits, SEEK_SET);
    origin_image->source = malloc(sizeof(struct source));
    origin_image->source = parse_image(image_f, origin_image->header->biWidth, origin_image->header->biHeight);
    fclose(image_f);

    return origin_image;
}

struct image *rotate(struct image *image)
{
    struct image *rotated_image = malloc(sizeof(struct image));
    rotated_image->header = malloc(sizeof(struct bmp_header));
    rotated_image->source = malloc(sizeof(struct source));

    rotated_image->source = rotate_image(image->source);
    rotated_image->header = rotate_h(image->header);

    return rotated_image;
}

void check_h(struct bmp_header h)
{
    // printf("%d\n", h.bfType);
    // printf("%d\n", h.bfileSize);
    // printf("%d\n", h.bfReserved);
    // printf("%d\n", h.bOffBits);
    // printf("%d\n", h.biSize);

    printf("%d\n", h.biWidth);
    printf("%d\n", h.biHeight);
    // printf("%d\n", h.biPlanes);
    // printf("%d\n", h.biBitCount);
    // printf("%d\n", h.biCompression);
    // printf("%d\n", h.biSizeImage);
    // printf("%d\n", h.biXPelsPerMeter);
    // printf("%d\n", h.biYPelsPerMeter);
    // printf("%d\n", h.biClrUsed);
    // printf("%d\n", h.biClrImportant);
}