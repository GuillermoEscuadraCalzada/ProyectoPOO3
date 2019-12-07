#ifndef TEXTURE_H
#define TEXTURE_H
#include "../../GameObject/GameObject.h"
#include "../../Graphics/Graphics/Graphics.h"
#include "../../GameManager/AssetManager/AssetManager.h"
class Texture : public GameObject
{
protected:
	bool clipped;
	SDL_Texture* texture;
	SDL_Texture* text;
	Graphics* graphics;
	int width, height;
	std::string path;
	SDL_Rect rect;
	SDL_Rect clippedRect;
public:
	Texture(std::string path, int x, int y);
	Texture(std::string path, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();

	std::string GetPath();
	void setPos(float x, float y);
	int GetWidth();
	int GetHeight();
	float GetX();
	float GetY();

	virtual void Render();
};

inline void Texture::setPos(float x, float y)
{
	rect.x = x;
	rect.y = y;
}

inline std::string Texture::GetPath()
{
	return path;
}
#endif // !TEXTURE_H
