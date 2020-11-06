#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "bmp_struct.h"


int main(void)
{
	FILE *file_image = fopen("sample.bmp", "rb");
	struct image *origin_image = read_image(file_image);

	puts("Header before: ");
	check_h(*(origin_image->header));

	struct image *rotated_image = rotate(origin_image);

	puts("Header after: ");
	check_h(*(rotated_image->header));

	FILE *new_img = fopen("output.bmp", "wb");

	write_image(rotated_image->source, rotated_image->header, new_img);

	fclose(new_img);

	return 0;
}
