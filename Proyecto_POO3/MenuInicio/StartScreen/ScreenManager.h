#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H


#include "../../MenuInicio/GameScreen/GameScreen.h"

class ScreenManager
{
	enum SCREENS {start, play};
	InputManager* input;
	StartScreen* startScreen;
	GameScreen* gameScreen;
	SCREENS currentScreen;
	static ScreenManager* instance;

public:
	static ScreenManager* getPTR();
	static void Release();
	void Update();
	void Render();

private:

	int selectedMode();
	ScreenManager();
	~ScreenManager();
};
#endif //!SCREENMANAGER_H