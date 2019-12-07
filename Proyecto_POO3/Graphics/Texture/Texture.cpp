#include "Texture.h"

/*Constructor de la clase Texture, requiere de un string que ser� la ubicaci�n de la imagen
	@param[ path ] ubiaci�n de donde se encuentra la imagen*/
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

/*Constructor de la clase texture que sirve para texturas animadas con im�genes que tienen m�s de un elemnto. Esto nos permite avanzar entre cada una para poder cambiar la textura actual
	@param[path] direcci�n de la textura dentro del archivo debug del juego
	@param[x] posici�n en la imagen en X donde comienza la animaci�n
	@param[y] posici�n de la imagen en Y donde comienza la animaci�n
	@param[w} anchura del segmento de la imagen
	@param[h] altura del segmento d ela imagen*/
Texture::Texture(std::string path, int x, int y, int w, int h)
{
	graphics = Graphics::returnPTR();	//Pregunta por el apuntador de la clase Graphics
	texture = AssetManager::getPTR()->GetTexture(path);	//Pregunta por el apuntador de la classe assetManager y luego busca la funci�n de GetTexture
	this->path = path;	//Path se igual al path del argumento
	clipped = true;	//Clipp es true

	width = w;	//width es igual a la w del argumento
	height = h;	//Height es igual a la h del argumento
	rect.w = width;	//La anchura de rect es igual a width
	rect.h = height;	//La altrua de rect es igual a height

	clippedRect.x = x;	//La posici�n de clippRect en X es igual a x
	clippedRect.y = y;	//La posici�n de clippRect en Y es igual a y
	clippedRect.w = w;	//La anchura de clippedRect es igual a la w del par�metro
	clippedRect.h = h;	//La altura de clippedRect es igual a la h del par�metro



}

/*Constructor de la clase texture que S�LO sirve para a�adir textos
	@param[text] el text que queremos que se imprima en la pantalla
	@param[fontPath] ubicaci�n del font dentro del archivo del juego
	@param[size] tama�o de las letras del texto.
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


void Texture::Render()
{
	Vector2 pos = Position();
	rect.x = (int)(pos.x - width * 0.5f);
	rect.y = (int)(pos.y - height * 0.5f);
	graphics->DrawTexture(texture, (clipped)? &clippedRect : NULL, &rect);
	graphics->DrawTexture(text,  NULL, &rect);
}
