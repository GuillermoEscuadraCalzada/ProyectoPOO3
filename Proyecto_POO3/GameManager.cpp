#include "GameManager.h"

GameManager* GameManager::ptr = nullptr;


/*Constructor principal de GameManager*/
GameManager::GameManager()
{
	quit = false;	//Quit es falso
	graphics = Graphics::returnPTR(); //Manda a llamar graphics junto con su función del apuntador
	//Si es falso, termina el update del juego
	if(!Graphics::returnPTR())
		quit = true;

	assetM = AssetManager::getPTR();

	texture = new Texture("Fondo.png");
}

/*Constructor principal del juego*/
GameManager::~GameManager()
{
	//Manda a llamar la función release del juego
	Graphics::Release();
	graphics = nullptr;	//Haz nulo este apuntador
	delete texture;
	texture = nullptr;
	AssetManager::Close();
	assetM = nullptr;
}



/*Esta función te permite inicializar esta clase, preguntando si ya existe un apuntador de esta clase*/
GameManager* GameManager::Initialize()
{
	//Si el apuntador es nulo, crea la función, si no, no hagas nada. no se puede volver a crear
	if(ptr == nullptr)
		ptr = new GameManager();

	return ptr;	//Regresa el apuntador
}

/*Update es la función del loop principal del juego*/
void GameManager::Update()
{
	while(!quit)
	{
		//Manda a llamar el sistema de eventos de SDL
		while(SDL_PollEvent(&eventHandler) != 0)
		{
			if(eventHandler.type == SDL_QUIT)	//Si se termina el programa, termina el loop
				quit = true;
		}

		graphics->ClearBackBuffer();

		texture->Render();

		graphics->Render();	//Actualiza constantemente el render del juego

	}
}

//Función que cierra esta clase y elimina todos los elementos del juego
void GameManager::Close()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
}
