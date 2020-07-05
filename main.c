#include <cairo.h>
#include <stdint.h>
#include <stdio.h>

int main() {
	cairo_surface_t *s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 4, 1);
	unsigned char * data = cairo_image_surface_get_data(s);
	cairo_t *cr = cairo_create(s);
	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);

#define SET_PIXEL(x, r, g, b, a) do { \
		cairo_set_source_rgba(cr, r, g, b, a); \
		cairo_rectangle(cr, x, 0, 1, 1); \
		cairo_fill(cr); \
	} while (0)

	SET_PIXEL(0, 1.0, 0.0, 0.0, 1.0);
	SET_PIXEL(1, 0.0, 1.0, 0.0, 1.0);
	SET_PIXEL(2, 0.0, 0.0, 1.0, 1.0);
	SET_PIXEL(3, 0.0, 0.0, 0.0, 1.0);
	cairo_destroy(cr);

#define SHOW_PIXEL(offset, name) printf("%6s: 0x%02x 0x%02x 0x%02x 0x%02x = 0x%08x\n", \
		name, data[offset+0], data[offset+1], data[offset+2], data[offset+3], \
		*(uint32_t*)&data[offset])

	SHOW_PIXEL(0*4, "red");
	SHOW_PIXEL(1*4, "green");
	SHOW_PIXEL(2*4, "blue");
	SHOW_PIXEL(3*4, "blank");

	cairo_surface_destroy(s);
	return 0;
}
