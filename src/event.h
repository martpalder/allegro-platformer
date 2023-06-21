#pragma once
#ifndef EVENT_H
#define EVENT_H
#include <allegro5/events.h>
#include <allegro5/display.h>

// Event queue
ALLEGRO_EVENT_QUEUE* createEventQueue(void);
void destroyEventQueue(ALLEGRO_EVENT_QUEUE* queue);
// Event source
ALLEGRO_EVENT_SOURCE* getKeyboardEventSrc(void);
ALLEGRO_EVENT_SOURCE* getDisplayEventSrc(ALLEGRO_DISPLAY* disp);
void registerEventSource(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT_SOURCE* src);
void unregisterEventSource(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT_SOURCE* src);
// Event get and wait
void getNextEvent(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT* pE);
void waitForEvent(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT* pE);

#endif
