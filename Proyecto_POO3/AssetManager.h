#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "Graphics.h"
#include "Vector.h"
#include <SDL_mixer.h>
#include <iostream>
using std::string;
class AssetManager
{
public:
	
	static AssetManager* getPTR();
	static void Close();

	SDL_Texture* GetTexture(string fileName);


private:
	static AssetManager* ptr;
	Vector<string> textures;


	AssetManager();
	~AssetManager();
	

};

#endif //! ASSETMANAGER_H
