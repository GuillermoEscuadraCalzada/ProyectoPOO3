#ifndef  GAMESCREEN_H
#define GAMESCREEN_H
#include "../../MenuInicio/StartScreen/StartScreen.h"
#include "../../GameManager/Timer/Timer.h"
#include "../../GameObject/GameObject.h"
#include "../../Graphs/Graph.h"
#include "../../GameObject/Sons/FirstBusiness.h"
class GameScreen : public GameObject
{
public:
	FirstBusiness first;
	
	void Update();
	void Render();
	void Init();
	GameScreen();
	~GameScreen();
	myVector<Texture*>* textureList;

private:
	Graph<Texture*> gameGraph;
	float score = 0;
	int time = 0;
	Timer* timer;
	InputManager* input;
	Texture* backGround;
	Texture* scoreBoard;
	Texture* grid;
};
#endif // ! GAMESCREEN_H
