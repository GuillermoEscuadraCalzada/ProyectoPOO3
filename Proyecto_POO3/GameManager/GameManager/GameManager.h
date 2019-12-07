#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../../Graphics/Graphics/Graphics.h"
#include "../../Graphics/AnimatedTextures/AnimatedTexture.h"
#include "../../MenuInicio/MenuInicio.h"
#include "../../myVector.h"
#include "../AudioManager/AudioManager.h"
#include "../../GameObject/GameObject.h"
#include "../InputManager/InputManager.h"

class GameManager
{
public:

	static GameManager* Initialize();
	static void Close();

	void Update();
	void Render();
	Texture* backGround; 
	int GetWidth()
	{
		return graphics->SCREEN_WIDTH;
	}
	int GetHeight()
	{
		return graphics->SCREEN_HEIGHT;
	}

private:
	static GameManager* ptr;

	GameObject* gameOBJ;
	Timer* timer;

	MenuInicio* menuInicio;
	bool quit;

	Graphics* graphics;
	AssetManager* assetM;
	AudioManager* audiMGR;
	InputManager* inputMGR;
	
	myVector<Texture*> textureVect;
	myVector<AnimatedTexture*> animVect;
	
	SDL_Event eventHandler;

	
	
	const int FrameRate = 60.0f;
	GameManager();
	~GameManager();
protected:
	void AddTexturesToVec();
private:
	Texture* text;
	Texture* text2;
	AnimatedTexture* anText;
};

#endif // !GAMEMANAGER_H
