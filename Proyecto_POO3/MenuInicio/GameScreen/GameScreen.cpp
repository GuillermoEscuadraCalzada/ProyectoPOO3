#include "GameScreen.h"
GraphNode<Texture*>* firstImage = nullptr;
GraphNode<Texture*>* newIMG = nullptr;


/*Constructor de la clase GameScreen*/
GameScreen::GameScreen()
{
	timer = Timer::getPTR();	//Busca el apuntador del tiempo
	input = InputManager::getPtr();	//Busca el apuntador del input
	backGround = new Texture("Fondo_800x800.png", 0, 0, 800, 800);	//Se carga la imagen del fondo
	backGround->Position(Vector2(400, 400));	//Se setea la posicón de la imagen al centro de la pantalla

	seekCharacter = new Texture("FirstBSNS.png", 0, 0, 70, 70);
	seekCharacter->Position(Vector2(400, 400));	//Se setea la posicón de la imagen al centro de la pantalla

}


GameScreen::~GameScreen()
{

	timer = nullptr;
	input = nullptr;
	
	delete backGround;
	backGround = nullptr;

	delete seekCharacter;
	seekCharacter = nullptr;
}

/*Actualización de la pantalla gameScreen, donde suceden todas las acciones del jugador, disminución del tiempo, etc.*/
void GameScreen::Update()
{
	input->Update();
	seekCharacter->SeekSB(input->MousePosition());
	input->UpdatePrevInput();
}
	
/*Función que renderiza cada elemento importante de esta ventana, los nodos del grafo, el fondo, el score y */
void GameScreen::Render()
{
	try
	{
		backGround->Render();
		seekCharacter->Render();
	} catch(exception & e)
	{
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}


/*Esta función inicializará los nodos del grafo para posicionarlos dentro de la pantalla*/
void GameScreen::Init()
{
	
}