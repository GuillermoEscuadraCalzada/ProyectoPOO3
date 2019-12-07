#include "GameManager/GameManager/GameManager.h"

/*
	Grid 8x8 Tamaño del mapa
	Implementar Música
	Implementar imágenes
	
*/

using std::cout; using std::endl; using std::string;

int main(int argc, char* args[])
{
	////int i = menus.showMenu(screen, font, screenWidth, screenHeight);
	////Si no se inicializa, imprime lo siguiente
	//if(!Initialize())
	//	printf("Failed to initialize!\n");
	//////Por otro lado, quit es falso;
	//else
	//	quit = false; //Main loop flag
	////Manda a llamar la función Update en caso de que sí logre iniciar el programa
	//Update();
	/////Al finalizar el update, manda a llamar la función close
	//close();

	GameManager* game = GameManager::Initialize();
	game->Update();
	GameManager::Close();
	game = nullptr;

	return 0;
}