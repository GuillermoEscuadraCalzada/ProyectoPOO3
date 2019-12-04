#include "MenuInicio.h"

int MenuInicio::showMenu(SDL_Surface* screen, TTF_Font* font)
{
	SDL_Color color = { 255, 255, 255 };
	
	int x, y;

	const int numMenu = 2;
	const char* labels[numMenu] = { "Start", "Exit" };	//Texto de los elementos del menú

	SDL_Surface* menus[numMenu];	//Arreglo de elementos en el menu
	bool selected[numMenu] = { 0,0 };	//Ambos elementos del arreglo son falose
	SDL_Color colour[2] = 
	{ 
		{255,255,255}, 
		{255,0,0}
	};	//Color del texto al estar seleccionados/no seleccionados

	menus[0] = TTF_RenderText_Solid(font, labels[0], colour[0]);
	menus[1] = TTF_RenderText_Solid(font, labels[1], colour[0]);

	SDL_Rect pos[numMenu];

	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;//Se obtiene la posición del texto en el ancho del primer elemento del arreglo de menús, dentro de la ventana
	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;//Se obtiene la posición del texto en lo alto del primer elemento del arreglo

	pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;//Se obtiene la posición del texto en el ancho del segundo elemento del arreglo de menús, dentro de la ventana
	pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;//Se obtiene la posición del texto en lo alto del segundo elemento del arreglo
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	SDL_Event eventHandler;
	while(1)
	{
		while(SDL_PollEvent(&eventHandler))
		{
			switch(eventHandler.type)
			{

			case SDL_QUIT:	//Si termina el programa, elimina todos los elementos de menu
			{
				for(int i = 0; i < numMenu; i++)
					SDL_FreeSurface(menus[i]);
				return 1;
			}

			case SDL_MOUSEMOTION:	//Detecta la posición del mouse dentro de la ventana
			{
				x = eventHandler.motion.x;	//Mouse en x
				y = eventHandler.motion.y;	//Mouse en y
				
				//Cicla por todo el arreglo del menú
				for(int i = 0; i < numMenu; i++)
				{
					//Si se encuentra en la posión de algún elemento del menú, cambia su color
					if(x >= pos[i].x && x <= pos[i].w  && y >= pos[i].y &&  y <= pos[i].y + pos[i].h)
					{
						//Si se encuentra en esta posición, muestra de color rojo
						if(!selected[i])
						{
							selected[i] = 1;	//Se vuelve verdadero este elemento
							SDL_FreeSurface(menus[i]);	//Libera el estado anterior
							menus[i] = TTF_RenderText_Solid(font, labels[i], colour[1]);	//Cambia su color
						}
					}
					else
					{
						//Si no fue seleccionado, cambia su color o déjalo en blanco
						if(selected[i])
						{
							selected[i] = 0;	//Se hace falso
							SDL_FreeSurface(menus[i]);	//Libera su estado anterior
							menus[i] = TTF_RenderText_Solid(font, labels[i], colour[0]);	//Lo cambia a blanco
						}
					}
				}
				break;
			}


			case SDL_MOUSEBUTTONDOWN:	//Detecta la posición del mouse y dónde es presionado
			{
				x = eventHandler.button.x;	//Mouse en x
				y = eventHandler.button.y;	//Mouse en y
				
				//Cicla y detecta si el mouse es presionado en alguna de las opciones en el arreglo de menu
				for(int i = 0; i < numMenu; i++)
				{
					//Si está en el rectángulo que le pertenece a cada una de las palabras
					if(x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						//Libera cada superficie
						for(int j = 0; j < numMenu; j++)
							SDL_FreeSurface(menus[j]);
						return i;
					}
				}
				break;
			}


			case SDL_KEYDOWN:
				if(eventHandler.key.keysym.sym == SDLK_ESCAPE)
				{
					for(int i = 0; i < numMenu; i++)
						SDL_FreeSurface(menus[i]);
					
					return 0;
				}

			}


		}
			for(int i = 0; i < numMenu; i++)
			{
				SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
			}
	}
}
