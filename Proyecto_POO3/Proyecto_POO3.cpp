#include "GameManager/GameManager/GameManager.h"

/*
	Grid 8x8 Tama�o del mapa
	Implementar M�sica
	Implementar im�genes
	
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
	////Manda a llamar la funci�n Update en caso de que s� logre iniciar el programa
	//Update();
	/////Al finalizar el update, manda a llamar la funci�n close
	//close();

	GameManager* game = GameManager::Initialize();
	game->Update();
	GameManager::Close();
	game = nullptr;

	return 0;
}