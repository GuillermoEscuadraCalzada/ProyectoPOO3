#include "Texture.h"

/*Constructor de la clase Texture, requiere de un string que será la ubicación de la imagen
	@param[ path ] ubiación de donde se encuentra la imagen*/
Texture::Texture(std::string path, int x, int y)
{
	graphics = Graphics::returnPTR();	//Manda a crear o llamar el apuntador de la clase graphics
	texture = AssetManager::getPTR()->GetTexture(path);	//Manda a llamar dos clases, AssetManagerPTR, donde obtiene su apuntador y luego GetTexture, donde consigue la imagen 
	this->path = path;
	clipped = false;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;

	
}

Texture::Texture(std::string path, int x, int y, int w, int h)
{
	graphics = Graphics::returnPTR();
	texture = AssetManager::getPTR()->GetTexture(path);
	this->path = path;
	clipped = true;

	width = w;
	height = h;
	rect.w = width;
	rect.h = height;

	clippedRect.x = x;
	clippedRect.y = y;
	clippedRect.w = w;
	clippedRect.h = h;



}

/*Constructor de la clase texture que SÓLO sirve para añadir textos
	@param[text] el text que queremos que se imprima en la pantalla
	@param[fontPath] ubicación del font dentro del archivo del juego
	@param[size] tamaño de las letras del texto.
	@param[ color ] color de las palabras*/
Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	graphics = Graphics::returnPTR();	//Llama el apuntador de graphics
	texture = AssetManager::getPTR()->GetText(text, fontPath, size , color);	//Obtiene el texto de assetManager
	path = AssetManager::getPTR()->text;

	clipped = false;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;
}

Texture::~Texture()
{
	
	texture = nullptr;
	graphics = nullptr;
}

int Texture::GetWidth()
{
	return rect.w;
}

int Texture::GetHeight()
{
	return rect.h;
}

float Texture::GetX()
{
	return rect.x;
}

float Texture::GetY()
{
	return rect.y;
}

void Texture::Render()
{
	Vector2 pos = Position();
	rect.x = (int)(pos.x - width * 0.5f);
	rect.y = (int)(pos.y - height * 0.5f);
	graphics->DrawTexture(texture, (clipped)? &clippedRect : NULL, &rect);
	graphics->DrawTexture(text,  NULL, &rect);
}
