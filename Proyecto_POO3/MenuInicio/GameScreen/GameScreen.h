#ifndef  GAMESCREEN_H
#define GAMESCREEN_H
#include "../../MenuInicio/StartScreen/StartScreen.h"
#include "../../GameManager/Timer/Timer.h"
#include "../../GameObject/GameObject.h"
class GameScreen : public GameObject
{
public:
	
	void Update();
	void Render();
	GameScreen();
	~GameScreen();
	myVector<Texture*>* textureList;

private:
	int score;
	Timer* timer;
	InputManager* input;
	Texture* backGround;
	Texture* scoreBoard;
	Texture* grid;
};
#endif // ! GAMESCREEN_H
