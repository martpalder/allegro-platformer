#include "./input.h"

void checkKeys(ALLEGRO_KEYBOARD_EVENT* pE, bool* pKeys)
{
	if (pE->type == ALLEGRO_EVENT_KEY_DOWN)
	{
		*(pKeys + pE->keycode) = 1;
	}
	else if (pE->type == ALLEGRO_EVENT_KEY_UP)
	{
		*(pKeys + pE->keycode) = 0;
	}
	//printf("%d\n", pE->keycode);
}
