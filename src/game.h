#pragma once
#ifndef GAME_H
#define GAME_H
#include <allegro5/events.h>
#include <allegro5/display.h>
#include <allegro5/allegro_font.h>

#define W 640
#define H 480
#define HALF_W W/2
#define HALF_H H/2
#define TILE_SZ 64
#define SPD 192

typedef struct {
	ALLEGRO_DISPLAY* disp;
	ALLEGRO_EVENT_QUEUE* queue;
} Game;

Game initGame(void);
void runGame(Game game);
void quitGame(Game game);

#endif
