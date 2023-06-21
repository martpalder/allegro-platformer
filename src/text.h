#pragma once
#ifndef TEXT_H
#define TEXT_H
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>

typedef struct {
	ALLEGRO_COLOR col;
	float x;
	float y;
} Text;

ALLEGRO_FONT* loadFont(const char* FILEPATH, const int SIZE);
void destroyFont(ALLEGRO_FONT* font);
Text createText(ALLEGRO_COLOR col, int x, int y);
void drawText(ALLEGRO_FONT* font, Text* pText, const char* STR);
void drawTextInt(ALLEGRO_FONT* font, Text* pText, const char* FORMAT, const int NUM);
void textbox(ALLEGRO_FONT* font, Text* pText, const char* STR);

#endif
