#ifndef  MENUINICIO_H
#define MENUINICIO_H

#include <SDL.h>
#include "../Graphics/Texture/Texture.h"
#include "SDL_ttf.h"

class MenuInicio
{

public:


	Texture* text;
	Texture* score;
	MenuInicio();
	~MenuInicio();
	
	
	void Init();
	void Update();
	bool continuee = true;
	int x, y;

	SDL_Color color[2] = 
	{
		{ 255,255,255, 0 },
		{255,255, 0,255}
	};

	SDL_Surface* title;

	SDL_Surface* menu[3];
	bool selected[3] = { 0, 0, 0 };
	
	SDL_Rect pos[4];
	SDL_Renderer* render = Graphics::returnPTR()->getRender();
private:
	SDL_Event eventHandler;

	SDL_Texture* Start;
	SDL_Texture* Exit;
	SDL_Texture* hScore;
	SDL_Texture* Title;
protected:
	void changeRender();
};


#endif // ! MENUINICIO_H

