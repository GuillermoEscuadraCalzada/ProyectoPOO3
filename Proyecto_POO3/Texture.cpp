#include "Texture.h"

/*Constructor de la clase Texture, requiere de un string que será la ubicación de la imagen
	@param[ path ] ubiación de donde se encuentra la imagen*/
Texture::Texture(std::string path)
{
	graphics = Graphics::returnPTR();	//Manda a crear o llamar el apuntador de la clase graphics
	texture = AssetManager::getPTR()->GetTexture(path);	//Manda a llamar dos clases, AssetManagerPTR, donde obtiene su apuntador y luego GetTexture, donde consigue la imagen 


	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	rect.w = width;
	rect.h = height;
}

Texture::~Texture()
{
	
	texture = nullptr;
	graphics = nullptr;
}

void Texture::Render()
{
	

	graphics->DrawTexture(texture);
}
