#ifndef  GAMESCREEN_H
#define GAMESCREEN_H
#include "../../MenuInicio/StartScreen/StartScreen.h"
#include "../../GameManager/Timer/Timer.h"
#include "../../GameObject/GameObject.h"
#include "../../Graphs/Graph.h"


class GameScreen : public GameObject
{
public:
	
	void Update();
	void Render();
	void Init();
	GameScreen();
	~GameScreen();
	myVector<Texture*>* textureList;

private:
	float score = 0;
	InputManager* input;
	int milisegundos = 0;
	int segundos = 0;
	int minutos = 0;
	float totalTime = 0;
	Timer* timer;
	Texture* backGround;
	Texture* seekCharacter;
};
#endif // ! GAMESCREEN_H
