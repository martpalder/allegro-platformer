#include <stdio.h>
#include <allegro5/altime.h>
#include "./init.h"
#include "./display.h"
#include "./event.h"
#include "./input.h"
#include "./audio.h"
#include "./sprite.h"
#include "./tile.h"
#include "./text.h"
#include "./camera.h"
#include "./collision.h"
#include "./color.h"
#include "./game.h"

Game initGame(void)
{
	Game game;

	// Initialize Allegro and its add-ons
	initAllegro();
	initImage();
	initAudio();
	initFont();
	initTTF();

	// Create a display window
	game.disp = createDisplay(W, H, "Allegro Game");

	// Create an event queue
	game.queue = createEventQueue();

	// Register event sources
	registerEventSource(game.queue, getKeyboardEventSrc());
	registerEventSource(game.queue, getDisplayEventSrc(game.disp));

	return game;
}

void quitGame(Game game)
{
	// Unregister event sources
	unregisterEventSource(game.queue, getDisplayEventSrc(game.disp));
	unregisterEventSource(game.queue, getKeyboardEventSrc());

	// Destroy queue and display
	destroyEventQueue(game.queue);
	destroyDisplay(game.disp);

	// Quit Allegro
	// and its add-ons
	//quitTTF();
	quitFont();
	quitImage();
	quitAudio();
	quitAllegro();
}

void runGame(Game game)
{
	// Variables
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT e;
	Audio audio;
	Camera cam;
	Text hudText;
	Text diaText;
	unsigned char i;
	double now, then, dt;
	float movestep, jumpStart;
	bool keys[ALLEGRO_KEY_MAX];
	bool lastEnter, isJumping, isGrounded, showText;
	char* str[] = {
		"Hello, player!",
		"This is a game made with Allegro.",
		"Good luck!"
	};

	// Resources
	// Tilesets
	Tileset mapTiles;
	Tileset playerTiles;
	// Sprites
	Sprite player;
	Sprite star;
	// Map
	Tilemap map1;

	// Set variables
	memset(&keys, 0, sizeof(keys));
	cam = (Camera){ 0, 0 };
	i = 0;
	then = 0.0f;
	lastEnter = 0;
	isJumping = 0;
	isGrounded = 0;
	showText = 0;

	// Load a font
	font = loadFont("fonts/arial.ttf", 24);

	// Create texts
	hudText = createText(YELLOW, 0, 0);
	diaText = createText(BLACK, 0, 16);

	// Load a tilemap
	map1 = loadTilemap("maps/map1.txt", 64);

	// Load graphics resources
	// Map
	mapTiles = loadTileset(
		"images/tiles.png",
		TILE_SZ, TILE_SZ
	);
	// Sprites
	player = createSprite(
		"images/stickman_anim.png",
		HALF_W - TILE_SZ>>1,
		HALF_H - TILE_SZ>>1,
		TILE_SZ, TILE_SZ<<1
	);
	star = createSprite(
		"images/star.png",
		448, 320,
		TILE_SZ, TILE_SZ
	);

	// Load and set up audio
	audio.data[0] = loadSample("sounds/jump.wav");
	audio.spl = createSampleInstance(audio.data[0]);
	audio.stream = loadStream("music/hey.mp3");

	// Main loop
	while (1)
	{
		// Get time
		now = al_get_time();
		dt = now - then;
		then = now;

		// Calculate movestep
		movestep = SPD * dt;

		// Get next event
		getNextEvent(game.queue, &e);

		// Handle the event
		if (&e)
		{
			checkKeys((ALLEGRO_KEYBOARD_EVENT*)&e, &keys);
			if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE || keys[ALLEGRO_KEY_ESCAPE])
			{
				break;
			}
		}

		// Handle input
		if (keys[ALLEGRO_KEY_LEFT])
		{
			// Move the player left
			moveSpriteLeft(&player, movestep);
			player.idx = 0;

			// Check tilemap collision
			if (isCollisionTilemap(&player, &map1, &mapTiles))
			{
				moveSpriteRight(&player, movestep);
			}
		}
		else if (keys[ALLEGRO_KEY_RIGHT])
		{
			// Move the player right
			moveSpriteRight(&player, movestep);
			player.idx = 1;

			// Check tilemap collision
			if (isCollisionTilemap(&player, &map1, &mapTiles))
			{
				moveSpriteLeft(&player, movestep);
			}
		}
		// Space: jump
		if (keys[ALLEGRO_KEY_SPACE] && !isJumping && isGrounded)
		{
			playSampleInstance(audio.spl);
			jumpStart = player.y;
			isJumping = 1;
			isGrounded = 0;
		}
		else if (!keys[ALLEGRO_KEY_SPACE])
		{
			isJumping = 0;
		}

		if (keys[ALLEGRO_KEY_ENTER] && !lastEnter)
		{
			lastEnter = 1;
			if (showText && ++i > 2)
			{
				showText = 0;
				i = 0;
			}
			else { showText = 1; }
		}
		else if (!keys[ALLEGRO_KEY_ENTER] && lastEnter)
		{
			lastEnter = 0;
		}

		// If jumping
		if (isJumping)
		{
			// Move up
			moveSpriteUp(&player, movestep);

			// If jump height reached
			if (player.y < jumpStart - 96.0f)
			{
				// Stop jumping
				isJumping = 0;
			}
			// If tilemap collision
			else if (isCollisionTilemap(&player, &map1, &mapTiles))
			{
				// Stop jumping
				moveSpriteDown(&player, movestep);
				isJumping = 0;
			}
		}
		// Otherwise
		else
		{
			// Move down
			moveSpriteDown(&player, movestep);

			// If tilemap collision
			if (isCollisionTilemap(&player, &map1, &mapTiles))
			{
				// Is grounded
				moveSpriteUp(&player, movestep);
				isGrounded = 1;
			}
		}

		// Check player bounds
		if (player.x < 0) { player.x = 0; }
		else if (player.x + player.tileset.tileW > map1.mapW * 64)
		{
			player.x = map1.mapW * 64 - player.tileset.tileW;
		}

		// Set camera x-position
		cam.x = player.x - HALF_W;

		// Check camera bounds
		if (cam.x < 0) { cam.x = 0; }
		else if (cam.x + W > map1.mapW * 64)
		{ cam.x = map1.mapW * 64 - W; }

		// Check sprite collisions
		if (isCollisionSprite(&player, &star))
		{
			puts("You got a star!");
		}

		// Clear screen
		clear(BLACK);

		// Draw a tilemap
		drawTilemap(&map1, &mapTiles, &cam);

		// Draw sprites
		drawSpriteRegion(&player, &cam);
		drawSprite(&star, &cam, star.tileset.bitmap);

		// Draw the textbox
		if (showText) { textbox(font, &diaText, str[i]); }

		// Draw FPS
		hudText.y = 0;
		drawTextInt(font, &hudText, "FPS: %d", (int)(1 / dt));
		//hudText.y = 16;
		//drawTextInt(font, &hudText, "Collision: %d", isCollisionTilemap(&player, &map1, &mapTiles));

		// Flip display
		flipDisplay();

		// Sleep until 33ms has passed
		while (al_get_time() < then + 0.033f);
	}

	// Destroy audio resources
	destroyStream(audio.stream);
	destroySample(audio.data[0]);
	destroySampleInstance(audio.spl);

	// Destroy graphics resources
	destroySprite(&player);
	destroyTileset(mapTiles);
	destroyTilemap(map1);

	// Destroy fonts
	destroyFont(font);
}
