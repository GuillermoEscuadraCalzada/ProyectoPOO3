#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Graphics.h"
#include "Texture.h"

class GameManager
{
public:

	static GameManager* Initialize();
	static void Close();

	void Update();
	Texture* texture;


private:
	static GameManager* ptr;

	bool quit;
	Graphics* graphics;
	AssetManager* assetM;

	SDL_Event eventHandler;
	
	GameManager();
	~GameManager();
};

#endif // !GAMEMANAGER_H
