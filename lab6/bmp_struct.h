#ifndef _BMP_STRUCT_H___
#define _BMP_STRUCT_H___

struct __attribute__((packed)) bmp_header
{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct __attribute__((packed)) pixel
{
    uint8_t b, g, r;
};

struct __attribute__((packed)) source
{
    uint32_t width, height;
    struct pixel *pixels;
};

struct __attribute__((packed)) image
{
    struct source *source;
    struct bmp_header *header;
};

#endif