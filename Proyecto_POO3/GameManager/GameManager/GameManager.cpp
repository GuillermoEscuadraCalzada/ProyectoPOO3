#include "GameManager.h"
GameManager* GameManager::ptr = nullptr;
AnimatedTexture* hollowKnight;


/*Constructor principal de GameManager*/
GameManager::GameManager()
{
	timer = Timer::getPTR();
	quit = false;	//Quit es falso
	graphics = Graphics::returnPTR(); //Manda a llamar graphics junto con su función del apuntador
	//Si es falso, termina el update del juego
	if(!Graphics::returnPTR())
		quit = true;

	assetM = AssetManager::getPTR();
	inputMGR = InputManager::getPtr();
	audiMGR = AudioManager::getPTR();
	screenMGR = ScreenManager::getPTR();
	gameOBJ = new GameObject(100.0f, 300.0f);
	
}

/*Destructor principal del juego, se cierran todas las clases que sean singleton y se eliminan apuntadores*/
GameManager::~GameManager()
{
	//Manda a llamar la función release del juego
	Graphics::Release();
	graphics = nullptr;	//Haz nulo este apuntador
	
	delete backGround;
	backGround = nullptr;

	AssetManager::Close();
	assetM = nullptr;

	AudioManager::Release();
	audiMGR = nullptr;

	InputManager::Release();
	inputMGR = nullptr;

	delete menuInicio;
	menuInicio = nullptr;

	Timer::Release();
	timer = nullptr;

	//ScreenManager::Release();
	//screenMGR = nullptr;

}




/*Esta función te permite inicializar esta clase, preguntando si ya existe un apuntador de esta clase*/
GameManager* GameManager::Initialize()
{
	//Si el apuntador es nulo, crea la función, si no, no hagas nada. no se puede volver a crear
	if(ptr == nullptr)
		ptr = new GameManager();
	return ptr;	//Regresa el apuntador
}

/*Inicializa el update de muchas funciónes que apenas están iniciando*/
void GameManager::EarlyUpdate()
{
	inputMGR->Update();
}



/*Update es la fucnión que actualiza todos los botones y estados del juego*/
void GameManager::Update()
{
	screenMGR->Update();
}

 void GameManager::LateUpdate()
{
	inputMGR->UpdatePrevInput();
	timer->Reset();
}

 /*El update principal del juego*/
void GameManager::MainUpdate()
{
	//menuInicio = new MenuInicio();
	//menuInicio->Update();
	audiMGR->PlayMusic("funkorama.mp3");
	while(!quit /*&& menuInicio->continuee*/)
	{
		timer->Update();

		//Manda a llamar el sistema de eventos de SDL
		while(SDL_PollEvent(&eventHandler) != 0)
		{
			if(eventHandler.type == SDL_QUIT)	//Si se termina el programa, termina el loop
				quit = true;

		}

		if(timer->DeltaTime() >= 1.0f / FrameRate)
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}

	}
}


/*Función que renderiza cada textura dentro del vector de texturas*/
void GameManager::Render()
{
	graphics->ClearBackBuffer();

	screenMGR->Render();

	graphics->Render();	//Actualiza constantemente el render del juego

}

//Función que cierra esta clase y elimina todos los elementos del juego
void GameManager::Close()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
}
