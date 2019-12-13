#ifndef  GAMESCREEN_H
#define GAMESCREEN_H
#include "../../MenuInicio/StartScreen/StartScreen.h"
#include "../../GameManager/Timer/Timer.h"
#include "../../GameObject/GameObject.h"
#include "../../Graphs/Graph.h"
#include "../../GameObject/Sons/firstBSNS.h"
#include "../../GameObject/Sons/SecondBSNS.h"
#include "../../GameObject/Sons/ThirdBSNS.h"
#include "../../GameObject/Sons/FourthBSNS.h"
#include "../../GameObject/Sons/FifthBSNS.h"
#include "../../GameObject/Sons/SixthBSNS.h"

class GameScreen : public GameObject
{
public:
	
	void Update();
	void Render();
	void Init();
	void UpdateNodesSons();
	GameScreen();
	~GameScreen();
	myVector<Texture*>* textureList;

private:
	void setupPosition(Texture* firstBSNS, Texture* secondBSNS, Texture* thirdBSNS, Texture* fourthBSNS, Texture* fifthBSNS, Texture* sixthBSNS, Vector2 pos);

	

	Graph<Texture*> gameGraph;
	float score = 0;
	InputManager* input;
	int milisegundos = 0;
	int segundos = 0;
	int minutos = 0;
	float totalTime = 0;
	Timer* timer;
	Texture* backGround;
	Texture* timeBoard;
	Texture* scoreBoard;
	Texture* grid;
};
#endif // ! GAMESCREEN_H
