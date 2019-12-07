#include "InputManager.h"

InputManager* InputManager::ptr = nullptr;

/*Funci�n que te regresa el apuntador de la clase InputManager para saber si ya fue creada o no
	@return apuntador de esta clase*/
InputManager* InputManager::getPtr()
{
	if(ptr == nullptr)
		ptr = new InputManager();
	return ptr;
}

/*Constructor principal por defecto de la clase InputManager, se inicializan todos los valores del mouse y del teclado*/
InputManager::InputManager()
{
	currentMouseState = NULL;
	prevMouseState = NULL;
	MouseXPos = MouseYPos = 0;
	keyBoardStates = SDL_GetKeyboardState(&keyLength);	//KeyBoard obtiene las teclas del teclado actual
	prevKeyState = new Uint8[keyLength];	//Se crea un arreglo de teclas para la variable prevKeyState
	memcpy(prevKeyState, keyBoardStates, keyLength);	//Se copian los valores del teclado actual a una variable previouse
}

/*Destructor de la clase InputManager*/
InputManager::~InputManager()
{
	delete[] prevKeyState;	//Elimina el arreglo que almacena las teclas 
	prevKeyState = NULL;
}

/*Se elimina el apuntador de esta clase*/
void InputManager::Release()
{
	delete ptr;
	ptr = nullptr;
}

#pragma region KeyBoard

/*Funci�n que te regresa verdadero al momento de tocar una tecla
	@param[scanCode] variable de sdl que detecta qu� tecla fue oprimida
	@return regresa verdadero en la tecla presionada dentro del enum de SDL_ScanCode*/
bool InputManager::keyDown(SDL_Scancode scanCode)
{
	return keyBoardStates[scanCode];
}

/*Esta funci�n pregunta qu� tecla fue presionada y si no estaba activa en PrevKeyState
	@para[scanCode] variable de SDL
	@return verdadero en la tecla que fue presionada del enum SDL_ScanCode*/
bool InputManager::keyPressed(SDL_Scancode scanCode)
{
	return !prevKeyState[scanCode] && keyBoardStates[scanCode];
}

/*Funci�n que nos permite saber si la tecla previamente presionada ya fue liberada
	@param[scanCode] variable de teclados dentro del enum SDL_Scancode
	@return falso en la tecla que fue liberada*/
bool InputManager::keyReleased(SDL_Scancode scanCode)
{
	return prevKeyState[scanCode] && !keyBoardStates[scanCode];
}

#pragma endregion Detecta si la tecla fue presionada o soltada


#pragma region Mouse

/*Observa qu� bot�n del mouse fue utilizada 
	@param[button] enum que guarda los botones del mouse
	@return verdadero al momento  de que un bot�n del mouse fue presionado*/
bool InputManager::MouseButtonDown(MOUSE_BUTTONS button)
{
	//Para sdl se necesita una variable que toma una "m�scara" para poder tomar el aspecto de botones del mouse
	Uint32 mask = 0;
	switch(button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;

	
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	


	case middle:
		mask = SDL_BUTTON_MMASK;
		break;



	case back:
		mask = SDL_BUTTON_X1MASK;

		break;
	case forward:

		mask = SDL_BUTTON_X2MASK;

		break;
	}

	return (currentMouseState & mask);	//Regresa si esta m�scara se encuentra activada en el estado actual del bot�n
}

/*Detecta qu� boti�n del mouse fue presionado y si est� presionado revisa que no est� presionado en el estado anterior al mouse
	@param[button] enum que guarda los botones del mouse
	@return regresa verdadero al momento de presionar un bot�n del mouse*/
bool InputManager::MouseButtonPressed(MOUSE_BUTTONS button)
{
	//Para sdl se necesita una variable que toma una "m�scara" para poder tomar el aspecto de botones del mouse
	Uint32 mask = 0;
	switch(button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;


	case right:
		mask = SDL_BUTTON_RMASK;
		break;



	case middle:
		mask = SDL_BUTTON_MMASK;
		break;



	case back:
		mask = SDL_BUTTON_X1MASK;

		break;
	case forward:

		mask = SDL_BUTTON_X2MASK;

		break;
	}

	return !(prevMouseState & mask)&&(currentMouseState & mask);	//Revisa si actualmente ese bot�n es falso en los estados anteriores del mouse y si se encuentra verdadero en el estado actual del mouse
}

/*Detecta qu� bot�n del mouse fue dejado de presionar
	@param[button[ enum que guarda los botones del mouse
	@return regresa falso en el bot�n que estaba presionado*/
bool InputManager::MouseButtonReleased(MOUSE_BUTTONS button)
{
	//Para sdl se necesita una variable que toma una "m�scara" para poder tomar el aspecto de botones del mouse
	Uint32 mask = 0;
	switch(button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;


	case right:
		mask = SDL_BUTTON_RMASK;
		break;



	case middle:
		mask = SDL_BUTTON_MMASK;
		break;



	case back:
		mask = SDL_BUTTON_X1MASK;

		break;
	case forward:

		mask = SDL_BUTTON_X2MASK;

		break;
	}
	//Regresa verdadero en caso de que la tecla previamente presionada se encuenttre en el estado de mouse previamente usado y que no est� en el mouse actual
	return (prevMouseState & mask) && !(currentMouseState & mask);
}

/*Regresa la posici�n del mouse dentro de la pantalla 
	@return posicion en x y y del mouse creando un nuevo vector2*/
Vector2 InputManager::MousePosition()
{
	return Vector2((float) MouseXPos, (float)MouseYPos);
}

#pragma endregi Detecta los botones del mouse usado

/*Actualiza la posici�n atual del mouse dentro de la pantalla, detectando su posic�n*/
void InputManager::Update()
{
	currentMouseState = SDL_GetMouseState(&MouseXPos, &MouseYPos);
}

/*Actualiza los estados y botones dentro de prevKeyIput y currentKeyInput*/
void InputManager::UpdatePrevInput()
{
	memcpy(prevKeyState, keyBoardStates, keyLength);
	prevMouseState = currentMouseState;
}

