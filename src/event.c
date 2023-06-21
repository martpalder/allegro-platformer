#include <stdio.h>
#include <allegro5/keyboard.h>
#include "./event.h"

ALLEGRO_EVENT_QUEUE* createEventQueue(void)
{
	ALLEGRO_EVENT_QUEUE* queue;
	queue = al_create_event_queue();
	if (!queue)
	{
		fprintf(stderr, "Failed to create an event queue!\n");
	}

	return queue;
}

void destroyEventQueue(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT_SOURCE* src)
{
	al_unregister_event_source(queue, src);
	al_destroy_event_queue(queue);
	src = (void*)0;
}

ALLEGRO_EVENT_SOURCE* getKeyboardEventSrc(void)
{
	return al_get_keyboard_event_source();
}

ALLEGRO_EVENT_SOURCE* getDisplayEventSrc(ALLEGRO_DISPLAY* disp)
{
	return al_get_display_event_source(disp);
}

void registerEventSource(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT_SOURCE* src)
{
	al_register_event_source(queue, src);
}

void unregisterEventSource(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT_SOURCE* src)
{
	al_unregister_event_source(queue, src);
}

void getNextEvent(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT* pE)
{
	al_get_next_event(queue, pE);
}

void waitForEvent(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT* pE)
{
	al_wait_for_event(queue,  pE);
}
