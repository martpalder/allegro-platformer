#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#include <allegro5/display.h>

ALLEGRO_DISPLAY* createDisplay(int w, int h, const char* title);
void destroyDisplay(ALLEGRO_DISPLAY* disp);
void clear(ALLEGRO_COLOR col);
void flipDisplay(void);

#endif
