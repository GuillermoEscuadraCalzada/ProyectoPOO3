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
	AddTexturesToVec();
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

}


/*Añade funcioens al vector de texturas y de animaciones*/
void GameManager::AddTexturesToVec()
{
	backGround = new Texture("Fondo.png",0, 0, 600, 600);
	
	backGround->Position(Vector2(300, 300));
	hollowKnight = new AnimatedTexture("Music.jpg",15, 64, 138, 83, 3, 2.0f, AnimatedTexture::horizontal);
	hollowKnight->Position(Vector2(300, 300));

	
	text = new Texture("Que tranza", "arial.ttf", 20, { 255, 0, 255 });
	text->Position(Vector2(100, 100));

	text2 = new Texture("Mames", "arial.ttf", 20, { 255, 10, 255 });
	text2->Position(Vector2(100,300));

	animVect.push_back(hollowKnight);
	textureVect.push_back(backGround);
	textureVect.push_back(text);
	textureVect.push_back(text2);
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

void GameManager::LateUpdate()
{
	inputMGR->UpdatePrevInput();
	timer->Reset();
}


/*Update es la fucnión que actualiza todos los botones y estados del juego*/
void GameManager::Update()
{

	if(inputMGR->keyDown(SDL_SCANCODE_W))
	{
		//hollowKnight->Translate(Vector2(0,-40.0f)*timer->DeltaTime());
		printf("W Key PresseD\n");
	}
	if(inputMGR->keyReleased(SDL_SCANCODE_S))
	{
		//hollowKnight->Translate(Vector2(0.0f, 40.0f) * timer->DeltaTime());
		printf("W Key Released\n");


	}
	if(inputMGR->MouseButtonPressed(InputManager::left))
	{
		//hollowKnight->Translate(Vector2(0.0f, 40.0f) * timer->DeltaTime());
		printf("Left Button Pressed\n");


	}
	if(inputMGR->MouseButtonReleased(InputManager::left))
	{
		//hollowKnight->Translate(Vector2(0.0f, 40.0f) * timer->DeltaTime());
		printf("Left button Released\n");

		
	}

}

/*El update principal del juego*/
void GameManager::MainUpdate()
{
	menuInicio = new MenuInicio();
	menuInicio->Update();
	while(!quit && menuInicio->continuee)
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



	(*textureVect.return_at(text->GetPath()))->Render();
	(*textureVect.return_at(backGround->GetPath()))->Render();
	(*animVect.return_at(hollowKnight->GetPath()))->Update();
	(*animVect.return_at(hollowKnight->GetPath()))->Render();
	//hollowKnight->WrapMode(AnimatedTexture::once);
	(*textureVect.return_at(text2->GetPath()))->Render();
	
	this->text->Render();

	graphics->Render();	//Actualiza constantemente el render del juego

}

//Función que cierra esta clase y elimina todos los elementos del juego
void GameManager::Close()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
}
