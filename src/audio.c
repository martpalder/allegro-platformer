#include <stdio.h>
#include "./audio.h"

ALLEGRO_SAMPLE_INSTANCE* createSampleInstance(ALLEGRO_SAMPLE* data)
{
	ALLEGRO_SAMPLE_INSTANCE* spl;
	spl = al_create_sample_instance(data);
	al_attach_sample_instance_to_mixer(spl, al_get_default_mixer());

	return spl;
}

ALLEGRO_SAMPLE* loadSample(const char* FILEPATH)
{
	ALLEGRO_SAMPLE* data = al_load_sample(FILEPATH);
	if (!data)
	{
		fprintf(stderr, "Failed to load audio sample: '%s'!\n", FILEPATH);
		exit(-1);
	}

	return data;
}

ALLEGRO_AUDIO_STREAM* loadStream(const char* FILEPATH)
{
	ALLEGRO_AUDIO_STREAM* stream = al_load_audio_stream(FILEPATH, 4, 2048);
	if (!stream)
	{
		fprintf(stderr, "Failed to load audio stream: '%s'!\n", FILEPATH);
		exit(-1);
	}
	al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());

	return stream;
}

void setSample(ALLEGRO_SAMPLE_INSTANCE* spl, ALLEGRO_SAMPLE* data)
{
	al_set_sample(spl, data);
}

void playSampleInstance(ALLEGRO_SAMPLE_INSTANCE* spl)
{
	if (al_get_sample_instance_playing(spl))
	{
		al_stop_sample_instance(spl);
	}
	al_play_sample_instance(spl);
}

void destroySampleInstance(ALLEGRO_SAMPLE_INSTANCE* spl)
{
	al_stop_sample_instance(spl);
	al_detach_sample_instance(spl);
	al_destroy_sample_instance(spl);
	spl = (void*)0;
}

void destroySample(ALLEGRO_SAMPLE* data)
{
	al_destroy_sample(data);
	data = (void*)0;
}

void destroyStream(ALLEGRO_AUDIO_STREAM* stream)
{
	al_detach_audio_stream(stream);
	al_destroy_audio_stream(stream);
	stream = (void*)0;
}
