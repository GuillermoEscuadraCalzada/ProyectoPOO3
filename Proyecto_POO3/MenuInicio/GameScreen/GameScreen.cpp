#include "GameScreen.h"

void GameScreen::Update()
{
	scoreBoard = new Texture("Score: " + std::to_string(score), "arialbd.ttf", 30, { 230, 200, 200 });	//Se carga el texto "Score" que irá sumando la puntuación del jugador
	scoreBoard->Position(Vector2(100, 20));	//Se pone en la esquina izquierda
	
}
	
void GameScreen::Render()
{
	backGround->Render();
	scoreBoard->Render();
	grid->Render();
}


/*Esta función inicializará los nodos del grafo para posxicionarlos dentro d ela pantalla*/
void GameScreen::Init()
{
	FirstBusiness* firstBSNS = new FirstBusiness("FirstBSNS.png", 0, 0, 70, 70);
	for(int i = 0; i < 64; i++)
	{
		int random = rand()% 6 + 1;
		if(random == 1)
		{
			GraphNode<Texture*>* node = new GraphNode<Texture*>(firstBSNS, Vector2(300,300));
			gameGraph.InsertNode(i, node);
		}
	}
	//gameGraph.InsertNode(NULL);
	


}

/*Constructor de la clase GameScreen*/
GameScreen::GameScreen()
{
	timer = Timer::getPTR();	//Busca el apuntador del tiempo
	input = InputManager::getPtr();	//Busca el apuntador del input

	backGround = new Texture("Fondo_800x800.png", 0, 0, 800, 800);	//Vuelve a cargar la textura de BackGround y la pone en el centro
	backGround->Position(Vector2(400, 400));	

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
