#include <iostream>
#include <string>
#include <SDL.h>
#include "MenuInicio.h"
using std::cout; using std::endl; using std::string;
bool Initialize(); void Draw(); void Update(); void close(); //Frees media and shuts down SDL

int screenWidth = 900;
int screenHeight = 800;
int texW = screenWidth;
int texH = screenHeight;
SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Window* screen;
SDL_Renderer* gRenderer = NULL; //The window renderer
TTF_Font* font;
bool quit;	//Booleano para cerrar o mantener abierto el prorama

MenuInicio menus;	//Menú de juego
SDL_Color color = { 255, 255, 255 };
SDL_Surface* surface;
SDL_Texture* texture;

int main(int argc, char* args[])
{
	//int i = menus.showMenu(screen, font, screenWidth, screenHeight);

	//Si no se inicializa, imprime lo siguiente
	if(!Initialize())
		printf("Failed to initialize!\n");
	////Por otro lado, quit es falso;
	else
		quit = false; //Main loop flag
	font = TTF_OpenFont("Assets/Fonts/arial.ttf", 32);

	//Manda a llamar la función Update en caso de que sí logre iniciar el programa
	Update();

	////Al finalizar el update, manda a llamar la función close
	close();


	return 0;
}


/*Esta función nos permitirá saber si la pantalla de juego se puede crear de manera correcta*/
bool Initialize()
{
	//Bandera que nos determinará si se logra abrir la ventana o no
	bool success = true;

	
	//Mensaje que muestra si no se inicializa la ventana
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else   //Si logra inicializar, sucederá esto
	{

		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Se crea la ventana de juego con las variables de ancho y altura
		gWindow = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

		//Si no logra crearse, presentará el siguiente mensaje
		if(gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else
		{	//Pero si logra crearse, empezaré con el ciclo de render de la ventana

			//Se crea el render de la ventana
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			
			//Si no logra crearse, muestra el siguiente mensaje
			if(gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else
			{	//En caso contrario, establece el siguiente color como el principal
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}

		TTF_Init(); //Función que inicializa la librería del texto
	}

	return success;	//Regresa verdadero o falso 
}


//Esta función nos mandará todo lo que decidamos colorear en la ventana de juego
void Draw()
{

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer); //Clear screen


	if(!font)
	{
		printf("No se cargo bien tu font\n");
	} else
	{
		surface = TTF_RenderText_Solid(font, "GG boys", color);
		texture = SDL_CreateTextureFromSurface(gRenderer, surface);
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { 0, 0, texW, texH };
		SDL_RenderCopy(gRenderer, texture, NULL, &dstrect);
	}
		SDL_RenderPresent(gRenderer); //Update screen

}

/*Función que actualizará todas las etapas del juego.*/
void Update()
{
	SDL_Event eventHandler; 	//Event handler



	while(!quit)
	{ //While application is running

		while(SDL_PollEvent(&eventHandler) != 0)
		{ //Handle events on queue
			if(eventHandler.type == SDL_QUIT)
			{ 
				quit = true;
			}
			switch(eventHandler.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				int i = menus.showMenu(surface, font);
				if(i == 1)
					quit = true;
				break;
			}
		}
		Draw();

	}
}


/*Función que cerrará la pantalla de juego y el juego en sí*/
void close()
{
	//Destruye todos los elementos del juego (ventana, texturas, etc.)
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	font = NULL;
	gWindow = NULL;
	gRenderer = NULL;
	surface = NULL;
	texture = NULL;

	menus.~MenuInicio();
	TTF_Quit();
	SDL_Quit();
}
