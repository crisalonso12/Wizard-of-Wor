//Using libs SDL, glibc
#include <SDL2/SDL.h>	//SDL version 2.0

#include <stdlib.h>
#include <stdio.h>



// Numbers bitmap, some routines and and SDL initialization taken from
// https://github.com/flightcrank/pong


// Please follow the coding guidelines described in:
// https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html



/* Do not use magic numbers in the code, define the meaning of the number
   in this section and the use the define across the code. This increases
   readability accross the code
*/


// The constants used to define the size of the window
#define SCREEN_WIDTH 960	//window height
#define SCREEN_HEIGHT 780	//window width

// The constants used for the movement of the block
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


// Block size that will be used for drawing on the screen
#define BLOCK_SIZE 50


// Coordinates of the starting player
#define PLAYER_START_X 20
#define PLAYER_START_Y 20

// For the return of the functions
#define SUCCESS 0
#define FAILURE 1

// Defines of the game states of each screen
#define START_SCREEN 0
#define LEVEL_1 1
#define GAME_OVER 2

// Defines for states
#define FALSE 0
#define TRUE 1

// The colors used in the game
#define BLACK 0x000000ff
#define WHITE 0xffffffff

// Timing delays
#define INPUT_DELAY_MS 500

// Time to render a frame in ms = 1000/60
#define FRAME_TIME_MS 16

// Movement diferential
#define MOVEMENT_DELTA 5



//function prototypes
//initialise SDL
int init_SDL(int w, int h, int argc, char *args[]);


// Avoid the use of global variables, modify the code to avoid its use.
int g_width, g_height;		//used if fullscreen

SDL_Window* window = NULL;	//The window we'll be rendering to
SDL_Renderer *renderer;		//The renderer SDL will use to draw to the screen

//surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *game_menu;

static SDL_Surface *puntos;
static SDL_Surface *interfaz_in_user;
static SDL_Surface *insert_coin;
static SDL_Surface *numblab;
static SDL_Surface *end;
static SDL_Surface *laberinto2;
static SDL_Surface *laberinto3;
static SDL_Surface *sprites;
static SDL_Surface *one_coin;
static SDL_Surface *two_coin;
static SDL_Surface *radar;

//textures
SDL_Texture *screen_texture;

// Always make a header for each one of the use created functions

/* Function: init_game
 * ---------------------------------
 * This function initialises the position of the player in the screen
 * (the block that can be moved with the WASD keys), and the block that
 * is part of the map, which is a test for collisions. Please note that
 * in this functions we are passing pointers, not values.
 *
 * Arguments:
 *	player:	Pointer to the player object
 *	map_element: Pointer to the map element object.
 *
 * Return:
 * 	void.
 */

/* Function: draw_menu
 * --------------------------------
 * This function is in charge of drawing the first screen that is
 * presented to the player.
 *
 * Arguments:
 *	none
 *
 * Return:
 *	void.
*/

/*
Description: a function that loads the menu image.
*/
static void portada() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = title->w;
	src.h = title->h;

	dest.x = (screen->w / 2) - (src.w / 2);
	dest.y = (screen->h / 2) - (src.h / 2);
	dest.w = title->w;
	dest.h = title->h;

	SDL_BlitSurface(title, &src, screen, &dest);
}


static void menu_juego() {

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = game_menu->w;
	src.h = game_menu->h;

	dest.x = 0;
	dest.y = 0;
	dest.w = game_menu->w;
	dest.h = game_menu->h;

	SDL_BlitSurface(game_menu, &src, screen, &dest);
}

/*
int inicio() {


	int quit = FALSE;
    portada();

	//render loop
	while(quit == FALSE) {

		//check for new events every frame
		SDL_PumpEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_ESCAPE]) {

            quit = 1;
        }

        if (keystate[SDL_SCANCODE_SPACE]) {
            menu_juego();
        }



		SDL_RenderClear(renderer);
		SDL_FillRect(screen, NULL, BLACK);


	return SUCCESS;

}
*/

// Main function

int main (int argc, char *args[]) {

	// Define the player and the maps
	//game_element_t player;

	// For the project the elements of the map should be created
	// dinamically (using malloc) and using linked lists.
	//game_element_t map_element;

	//SDL Window setup
	if (init_SDL(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == FAILURE) {

		return FAILURE;
	}


	SDL_GetWindowSize(window, &g_width, &g_height);
    int sleep = 0;

	int quit = FALSE;
    portada();

	//render loop
	while(quit == FALSE) {

		//check for new events every frame
		SDL_PumpEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_ESCAPE]) {

            quit = TRUE;
        }

        if (keystate[SDL_SCANCODE_SPACE]) {
            menu_juego();
        }



		//SDL_RenderClear(renderer);
		//SDL_FillRect(screen, NULL, BLACK);

	//inicio();


		SDL_UpdateTexture(screen_texture, NULL, screen->pixels,
						  screen->w * sizeof (Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		//draw to the display
		SDL_RenderPresent(renderer);

		//time it takes to render  frame in milliseconds
		//next_game_tick += FRAME_TIME_MS;
		//sleep = next_game_tick - SDL_GetTicks();

		if( sleep >= 0 ) {

			SDL_Delay(sleep);
		}
	}

	//free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_FreeSurface(game_menu);
	SDL_FreeSurface(end);

	//free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return SUCCESS;

}

/* Function: init_SDL
 * ----------------------------
 * This function initialises the required environment for SDL
 * to work.
 *
 * Arguments:
 *	width: The width of the screen.
 * 	height: The height of the screen.
 *	argc: The same parameter from the main function.
 *	args: The same parameter from the main function.
 *
 * Return:
 *	SUCCESS if no problem reported.
 *	FAILURE if any initialization failed
 */
int init_SDL(int width, int height, int argc, char *args[]) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

		return FAILURE;
	}

	int i;

	for (i = 0; i < argc; i++) {

		//Create window
		if(strcmp(args[i], "-f")) {

			SDL_CreateWindowAndRenderer(SCREEN_WIDTH,
										SCREEN_HEIGHT,
										SDL_WINDOW_SHOWN,
										&window,
										&renderer);

		} else {

			SDL_CreateWindowAndRenderer(SCREEN_WIDTH,
										SCREEN_HEIGHT,
										SDL_WINDOW_FULLSCREEN_DESKTOP,
										&window,
										&renderer);
		}
	}

	if (window == NULL) {

		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

		return FAILURE;
	}

	// Create the screen surface where all the elements will be drawn
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
											SDL_PIXELFORMAT_RGBA32);

	if (screen == NULL) {

		printf("Could not create the screen surfce! SDL_Error: %s\n",
			   SDL_GetError());

		return FAILURE;
	}

	// Create the screen texture to render the screen surface to the actual
	// display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);

	if (screen_texture == NULL) {

		printf("Could not create the screen_texture! SDL_Error: %s\n",
				SDL_GetError());

		return FAILURE;
	}

	//Load the title image
	title = SDL_LoadBMP("title.bmp");

	if (title == NULL) {

		printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

		return FAILURE;
	}

	//Load the game_menu image
	game_menu = SDL_LoadBMP("wiz.bmp");

	if (game_menu == NULL) {

		printf("Could not Load game_menu image! SDL_Error: %s\n",
				SDL_GetError());

		return FAILURE;
	}

		//Carga la imagen del puntos
	puntos = SDL_LoadBMP("puntos.bmp");

	if (puntos == NULL) {

		printf("Could not Load puntos image! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Carga la imagen laberinto3
	laberinto3 = SDL_LoadBMP("laberinto3.bmp");

	if (laberinto3 == NULL) {

		printf("La imagen laberinto3 no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}
	//Carga la imagen laberinto2
	laberinto2 = SDL_LoadBMP("laberinto2.bmp");

	if (laberinto2 == NULL) {

		printf("La imagen laberinto2 no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Carga la imagen radar
	radar = SDL_LoadBMP("radar.bmp");

	if (radar == NULL) {

		printf("La imagen radar no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Carga la imagen insert_coin
	insert_coin = SDL_LoadBMP("insert_coin.bmp");

	if (insert_coin == NULL) {

		printf("La imagen intert_coin no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	one_coin = SDL_LoadBMP("one_coin.bmp");

	if (one_coin == NULL) {

		printf("La imagen one_coin no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	two_coin = SDL_LoadBMP("two_coin.bmp");

	if (two_coin == NULL) {

		printf("La imagen two_coin no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}
	//carga los sprites
	sprites = SDL_LoadBMP("sprites.bmp");

	if (sprites == NULL) {

		printf("La imagen sprites no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//carga la imagen numblab
	numblab = SDL_LoadBMP("numblab.bmp");

	if (numblab == NULL) {

		printf("La imagen numblab no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	interfaz_in_user = SDL_LoadBMP("interfaz_in_user.bmp");

	if (interfaz_in_user == NULL) {

		printf("La imagen nterfaz_in_user no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//carga la imagen gameover
	end = SDL_LoadBMP("gameover.bmp");

	if (end == NULL) {

		printf("La imagen end no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}


	// Set the title colourkey.
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 0);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(game_menu, SDL_TRUE, colorkey);

	return SUCCESS;
}
