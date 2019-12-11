#include "GameManager/GameManager/GameManager.h"
#include <ctime>
/*
	Grid 8x8 Tamaño del mapa
	Implementar Música
	Implementar imágenes
	
*/

using std::cout; using std::endl; using std::string;

int main(int argc, char* args[])
{

	srand(time(nullptr));
	GameManager* game = GameManager::Initialize();

	game->MainUpdate();
	GameManager::Close();
	game = nullptr;

	return 0;
}