#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL.H>

class InputManager
{
public:
	static InputManager* getPtr();
	static void Release();

	bool keyDown(SDL_Scancode scanCode);
	void Update();

private:
	static InputManager* ptr;
	const Uint8* keyBoardStates;
	InputManager();
	~InputManager();
};



#endif // !INPUTMANAGER_H
