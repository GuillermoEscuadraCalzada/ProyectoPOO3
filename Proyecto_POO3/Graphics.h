#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_image.h>
#include "Vector.h"

class Graphics
{
public:
	static const int SCREEN_WIDTH = 700;
	static const int SCREEN_HEIGHT = 700;

	static Graphics* returnPTR();
	static void Release();

	SDL_Texture* LoadTexture(std::string path, Vector<std::string>& vector);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text);

	void ClearBackBuffer();
	void DrawTexture(SDL_Texture* texture);

	void Render();
	bool Init();

	SDL_Renderer* getRender()
	{
		return renderer;
	}



private:
	static Graphics* ptr;
	static bool initialize;

	SDL_Window* mainWindow;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	Graphics();
	~Graphics();

};


#endif 