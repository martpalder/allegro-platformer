#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "./init.h"

void initAllegro(void)
{
	// Init Allegro
	if(al_init() == 0)
	{
		fprintf(stderr, "Failed to init Allegro!\n");
		exit(-1);
	}
	// Install keyboard driver
	if (al_install_keyboard() == 0)
	{
		fprintf(stderr, "Failed to init keyboard driver!\n");
		exit(-1);
	}
	// Initialize primitives add-on
	if (al_init_primitives_addon() == 0)
	{
		fprintf(stderr, "Failed to init Allegro Primitives add-on!\n");
		exit(-1);
	}
}

void initAudio(void)
{
	if (al_install_audio() == 0)
	{
		fprintf(stderr, "Failed to init Allegro Image add-on!\n");
		exit(-1);
	}
	al_reserve_samples(16);
	al_init_acodec_addon();
}

void initImage(void)
{
	if (al_init_image_addon() == 0)
	{
		fprintf(stderr, "Failed to init Allegro Image add-on!\n");
		exit(-1);
	}
}

void initFont(void)
{
	if (!al_init_font_addon())
	{
		fprintf(stderr, "Failed to init Allegro Font add-on!\n");
		exit(-1);
	}
}

void initTTF(void)
{
	if (!al_init_ttf_addon())
	{
		fprintf(stderr, "Failed to init Allegro TTF add-on!\n");
		exit(-1);
	}
}

void quitAllegro(void)
{
	al_shutdown_primitives_addon();
	al_uninstall_keyboard();
	al_uninstall_system();
}

void quitAudio(void)
{
	al_uninstall_audio();
}

void quitImage(void)
{
	al_shutdown_image_addon();
}

void quitFont(void)
{
	al_shutdown_font_addon();
}

void quitTTF(void)
{
	al_shutdown_ttf_addon();
}