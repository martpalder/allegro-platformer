#include <stdio.h>
#include <allegro5/drawing.h>
#include <allegro5/allegro_native_dialog.h>
#include "./display.h"

ALLEGRO_DISPLAY* createDisplay(int w, int h, const char* title)
{
	ALLEGRO_DISPLAY* disp;
	disp = al_create_display(w, h);
	if (disp == (void*)0)
	{
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}
	al_set_window_title(disp, title);

	return disp;
}

void destroyDisplay(ALLEGRO_DISPLAY* disp)
{
	al_destroy_display(disp);
	disp = (void*)0;
}

void clear(ALLEGRO_COLOR col)
{
	al_clear_to_color(col);
}

void flipDisplay(void)
{
	al_flip_display();
}
