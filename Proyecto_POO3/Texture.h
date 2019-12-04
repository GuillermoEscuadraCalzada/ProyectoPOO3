#ifndef TEXTURE_H
#define TEXTURE_H
#include "AssetManager.h"
class Texture
{
	SDL_Texture* texture;
	Graphics* graphics;
	int width, height;

	SDL_Rect rect;

public:
	Texture(std::string path);
	~Texture();

	virtual void Render();
};


#endif // !TEXTURE_H
