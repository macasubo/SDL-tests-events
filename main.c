#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

int			main(int argc, char *argv[])
{
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Surface *screen;
	SDL_Surface *img;
	SDL_Surface *zozor;
	SDL_Rect position;
	SDL_Event event;
	int continuer;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "SDL_Init Error : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	win = SDL_CreateWindow("Hellow World", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error : %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}


	screen = SDL_GetWindowSurface(win);
	if (screen == NULL)
	{
		fprintf(stderr, "SDL_GetWindowSurface Error : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	/*for (x = 0; x < 256; x++)
	{
		for (y = 0; y < 700; y++)
		{
			position.x = y;
			position.y = x;
			drawing[x][y] = SDL_CreateRGBSurface(SDL_SWSURFACE, 1, 1, 32, 0, 0, 0, 0);
			SDL_FillRect(drawing[x][y], NULL, SDL_MapRGB(screen->format, x, x, x));
			SDL_BlitSurface(drawing[x][y], NULL, screen, &position);
			SDL_FreeSurface(drawing[x][y]);
		}
		y = 0;
	}*/

	/*position.x = 0;
	position.y = 0;
	img = IMG_Load("images/lac_en_montagne.bmp");
	if (img == NULL)
	{
		fprintf(stderr, "SDL_LoadBMP Error : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(img, NULL, screen, &position);
*/

	zozor = SDL_LoadBMP("images/zozor.bmp");
	position.x = screen->w / 2 - zozor->w / 2;
	position.y = screen->h / 2 - zozor->h / 2;
	if (zozor == NULL)
	{
		fprintf(stderr, "SDL_LoadBMP Error : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_SetColorKey(zozor, SDL_TRUE, SDL_MapRGB(zozor->format, 0, 0, 255));
	if (SDL_SetSurfaceAlphaMod(zozor, 200) != 0)
	{
		fprintf(stderr, "SDL_SetSurfaceAlphaMod Error : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_SetSurfaceBlendMode(zozor, SDL_BLENDMODE_BLEND);
	SDL_BlitSurface(zozor, NULL, screen, &position);


	//position.x = 200;
	//position.y = 200;
	/*sapin = IMG_Load("images/sapin.png");
	if (sapin == NULL)
	{
		fprintf(stderr, "IMG_Load Error : %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_BlitSurface(sapin, NULL, screen, &position);
*/

	SDL_ShowCursor(SDL_DISABLE);
	continuer = 42;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_UP:
						position.y--;
						break;
					case SDLK_DOWN:
						position.y++;
						break;
					case SDLK_RIGHT:
						position.x++;
						break;
					case SDLK_LEFT:
						position.x--;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				/*if (event.button.button == SDL_BUTTON_LEFT)
				{
					position.x = event.button.x;
					position.y = event.button.y;
				}*/
				if (event.button.button == SDL_BUTTON_RIGHT)
					continuer = 0;
				break;
			case SDL_MOUSEMOTION:
				position.x = event.motion.x;
				position.y = event.motion.y;
				break;
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		SDL_BlitSurface(zozor, NULL, screen, &position);

		if (SDL_UpdateWindowSurface(win) != 0)
		{
			fprintf(stderr, "SDL_UpdateWindowSurface Error : %s\n", SDL_GetError());
			SDL_DestroyWindow(win);
			SDL_Quit();
			exit(EXIT_FAILURE);
		}
	}


	SDL_FreeSurface(img);
	SDL_Quit();

	return EXIT_SUCCESS;
}