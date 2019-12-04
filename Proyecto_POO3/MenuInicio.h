#ifndef  MENUINICIO_H
#define MENUINICIO_H

#include <SDL.h>
#include "Texture.h"
#include "SDL_ttf.h"

class MenuInicio
{
public:
	MenuInicio();
	~MenuInicio();
	void Update();
	void Render();
	int x, y;
	bool selected[2] = { 0,0 };
	const char* labels[2] = { "Start", "Exit" };

	SDL_Color color[2] = {
		{ 255,0,255, 255 },
	{0,255,0,255}
	};

	SDL_Surface* menu[2];
	SDL_Rect pos[2];
	
private:
	SDL_Event eventHandler;
	SDL_Texture* Start;
	SDL_Texture* Exit;
};


#endif // ! MENUINICIO_H

