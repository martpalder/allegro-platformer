#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include "./color.h"
#include "./text.h"

ALLEGRO_FONT* loadFont(const char* FILEPATH, const int SIZE)
{
	ALLEGRO_FONT* font;
	font = al_load_font(FILEPATH, SIZE, 0);
	if (!font)
	{
		fprintf(stderr, "Failed to load a font: '%s'!\n", FILEPATH);
		exit(-1);
	}

	return font;
}

void destroyFont(ALLEGRO_FONT* font)
{
	al_destroy_font(font);
	font = (void*)0;
}

Text createText(ALLEGRO_COLOR col, int x, int y)
{
	return (Text) { col, x, y };
}

void drawText(ALLEGRO_FONT* font, Text* pText, const char* STR)
{
	al_draw_text(font, pText->col, pText->x, pText->y, 0, STR);
}

void drawTextInt(ALLEGRO_FONT* font, Text* pText, const char* FORMAT, const int NUM)
{
	al_draw_textf(font, pText->col, pText->x, pText->y, 0, FORMAT, NUM);
}

void textbox(ALLEGRO_FONT* font, Text* pText, const char* STR)
{
	al_draw_filled_rectangle(32, 480 - 160, 640 - 32, 480 - 32, WHITE);
	al_draw_text(font, pText->col, 48, 480 - 144, 0, STR);
}
