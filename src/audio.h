#pragma once
#ifndef AUDIO_H
#define AUDIO_H
#include <allegro5/allegro_audio.h>

typedef struct {
	ALLEGRO_SAMPLE* data[16];
	ALLEGRO_SAMPLE_INSTANCE* spl;
	ALLEGRO_AUDIO_STREAM* stream;
} Audio;

ALLEGRO_SAMPLE_INSTANCE* createSampleInstance(ALLEGRO_SAMPLE* data);
ALLEGRO_SAMPLE* loadSample(const char* FILEPATH);
ALLEGRO_AUDIO_STREAM* loadStream(const char* FILEPATH);
void setSample(ALLEGRO_SAMPLE_INSTANCE* spl, ALLEGRO_SAMPLE* data);
void playSampleInstance(ALLEGRO_SAMPLE_INSTANCE* spl);
void destroySampleInstance(ALLEGRO_SAMPLE_INSTANCE* spl);
void destroySample(ALLEGRO_SAMPLE* data);
void destroyStream(ALLEGRO_AUDIO_STREAM* stream);

#endif
