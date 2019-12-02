#ifndef  MENUINICIO_H
#define MENUINICIO_H

#include <SDL.h>
#include "SDL_ttf.h"

class MenuInicio
{
public:
	int showMenu(SDL_Surface* screen, TTF_Font* font);
	MenuInicio() {};
	~MenuInicio() {};

};


#endif // ! MENUINICIO_H

