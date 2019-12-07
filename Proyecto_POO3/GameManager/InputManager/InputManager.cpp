#include "InputManager.h"

InputManager* InputManager::ptr = nullptr;

InputManager* InputManager::getPtr()
{
	if(ptr == nullptr)
		ptr = new InputManager();
	return ptr;
}

void InputManager::Release()
{
	delete ptr;
	ptr = nullptr;
}

bool InputManager::keyDown(SDL_Scancode scanCode)
{
	return keyBoardStates[scanCode];
}

void InputManager::Update()
{
	keyBoardStates = SDL_GetKeyboardState(nullptr);
}

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{
}
