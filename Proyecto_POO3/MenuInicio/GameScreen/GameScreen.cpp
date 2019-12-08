#include "GameScreen.h"

void GameScreen::Update()
{
}

void GameScreen::Render()
{
	backGround->Render();
	scoreBoard->Render();
	grid->Render();
}

/*Constructor de la clase GameScreen*/
GameScreen::GameScreen()
{
	timer = Timer::getPTR();	//Busca el apuntador del tiempo
	input = InputManager::getPtr();	//Busca el apuntador del input

	backGround = new Texture("Fondo_800x800.png", 0, 0, 800, 800);	//Vuelve a cargar la textura de BackGround y la pone en el centro
	backGround->Position(Vector2(400, 400));	
	
	score = 100;
	scoreBoard = new Texture("Score: " + std::to_string(score), "arialbd.ttf", 30, { 230, 200, 200 });	//Se carga el texto "Score" que irá sumando la puntuación del jugador
	scoreBoard->Position(Vector2(100, 20));	//Se pone en la esquina izquierda

	grid = new Texture("Tablero.png", 0, 0, 580, 579);	//Carga una imagen que delimitará la posición de las imágenes de los objetos del juego
	grid->Position(Vector2(400, 400));
}

GameScreen::~GameScreen()
{
	
	
	timer = nullptr;
	backGround = nullptr;
	scoreBoard = nullptr;
	input = nullptr;
}
