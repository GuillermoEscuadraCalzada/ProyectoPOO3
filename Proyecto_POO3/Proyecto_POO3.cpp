#include "GameManager/GameManager/GameManager.h"
#include <ctime>
/*
	Grid 8x8 Tama�o del mapa
	Implementar M�sica
	Implementar im�genes
	Ayuda obtenida de:
	https://www.youtube.com/watch?v=ATa_joa6Gzg&list=PLhJr2LOK-xwxQlevIZ97ZABLw72Eu9he7
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