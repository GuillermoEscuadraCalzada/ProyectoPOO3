#include "AssetManager.h"

AssetManager* AssetManager::ptr = nullptr;



AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	textures.destroyTextures();
}


AssetManager* AssetManager::getPTR()
{
	if(ptr == nullptr)
		ptr = new AssetManager();

	return ptr;
}

void AssetManager::Close()
{
	delete ptr;
	ptr = nullptr;

}

/*Esta funci�n busca la direcci�n de la imagen dentro de los achivos
	@param[ filenName ]  Nombre de la textura dentro del archivo del proyecto
	@return un apuntador a SDL_Texture*/
SDL_Texture* AssetManager::GetTexture(std::string fileName)
{
	std::string fullPath = SDL_GetBasePath();	//Este string con la funci�n SDL_GetBasePath busca dentro de todos los archivos hasta encontrar con la ubicaci�n correcta del Debug
	fullPath.append("Assets/Textures/" + fileName);	//Esto toma el archivo donde guardaremos la direcci�n y le a�adir� el nombre de la imagen

	/*Si esta funci�n regresa nula*/
	if(textures.returnTexture(fullPath) == NULL)
	{
		//Crea una variable SDL_Texture y carga una textura al vector de texturas
		SDL_Texture* text = Graphics::returnPTR()->LoadTexture(fullPath, textures);
		return text;	//Regresa esta textura
	}else
		return nullptr;
	
}

