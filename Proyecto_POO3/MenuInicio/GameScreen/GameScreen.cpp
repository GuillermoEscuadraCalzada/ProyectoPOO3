#include "GameScreen.h"
GraphNode<Texture*>* firstImage = nullptr;
GraphNode<Texture*>* newIMG = nullptr;
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
	timeBoard = nullptr;
	input = nullptr;
}

/*Actualización de la pantalla gameScreen, donde suceden todas las acciones del jugador, disminución del tiempo, etc.*/
void GameScreen::Update()
{
	input->Update();

	milisegundos++;
	if(milisegundos == 60)
	{
		segundos++;
		milisegundos = 0;
	} else if(segundos == 60)
	{
		minutos++;
		segundos = 0;
		milisegundos = 0;
	}
	totalTime = minutos + segundos + milisegundos;
	timeBoard = new Texture("Time: " + to_string(minutos) + ":" + to_string(segundos) + ":" + to_string(milisegundos), "arialbd.ttf", 30, { 230, 200, 200 });	//Se carga el texto "Score" que irá sumando la puntuación del jugador
	scoreBoard = new Texture("Score: " + to_string(score), "arialbd.ttf", 30, { 230, 200, 200 });
	timeBoard->Position(Vector2(100, 20));	//Se pone en la esquina izquierda
	scoreBoard->Position(Vector2(Graphics::SCREEN_WIDTH - 200, Graphics::SCREEN_HEIGHT - Graphics::SCREEN_HEIGHT + 50));
	bool pressed = false;

	/*Cuando el tiempo tota*/
	if(totalTime > 1.0)
	{
		//Realizar una acción cuando el botón izquiero del mouse es presionado
		if(input->MouseButtonPressed(InputManager::left))
		{
			pressed = true;	//Pressed se vuelve verdadero
			if(!newIMG)
			{//Si newIMG es nulo
				firstImage = gameGraph.list->detectMouse(gameGraph.list->first, input->MousePosition(), pressed);	//Busca una imagen en la posición del mouse
				newIMG = firstImage;	//newIMG es igual a esa imagen
				firstImage = nullptr;	//Hazla nula
			}
			else
			{	//Si no lo es
				firstImage = gameGraph.list->detectMouse(gameGraph.list->first, input->MousePosition(), pressed);	//Guarda una nueva imagen
				if(firstImage != newIMG)
				{	//Compara y ve que no sean nulas
					gameGraph.list->swap(firstImage, newIMG);	//Cambia la posición de las imágenes
					gameGraph.list->addSons(gameGraph.list->first);	//Agrega los hijos a cada imagen
					gameGraph.list->bool_to_false(gameGraph.list->first);	//Regresa los booleanos a falso
					gameGraph.list->deleteImages(gameGraph.list->first);
					gameGraph.list->Update(gameGraph.list->first);
					score += 100;
				}
				firstImage = nullptr;
				newIMG = nullptr;
			}

		}
		
	}

	input->UpdatePrevInput();
}
	
/*Función que renderiza cada elemento importante de esta ventana, los nodos del grafo, el fondo, el score y */
void GameScreen::Render()
{
	backGround->Render();
	timeBoard->Render();
	scoreBoard->Render();
	grid->Render();
	gameGraph.list->renderNode(gameGraph.list->first);
}


/*Esta función inicializará los nodos del grafo para posicionarlos dentro de la pantalla*/
void GameScreen::Init()
{
	Vector2 position(120, 120);	//Una variable que guarda una variable que es la posición del primer nodo
	GraphNode<Texture*>* node = nullptr;	//Un nodo empezando en nulo
	
	//Se hará un ciclo con i y j para poder recorrer la lista de nodos de la lista del grafo
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			Vector2 pos = position;	//Se crea un nuevo vector de posión
			int random = rand() % 6 + 1;	//Se hace una variable que será random para poder elegir qué imagen se ingresará al nodo

			/*Se crean variables de las imágenes que vamos a utilizar para cada nodo, Se crean aquí porque si no la posición de cada imagen se actualizará con la última
			actualización del vector "pos"*/
			firstBSNS* firstB = new firstBSNS("FirstBSNS.png", 0, 0, 70, 70);
			SecondBSNS* secondBSNS = new SecondBSNS("FirstBSNS.png", 0, 0, 70, 70);
			ThirdBSNS* thirdBSNS = new ThirdBSNS("ThirdBSNS.png", 0, 0, 70, 70);
			FourthBSNS* fourthBSNS = new FourthBSNS("FourthBSNS.png", 0, 0, 70, 70);
			FifthBSNS* fifthBSNS = new FifthBSNS("FifthBSNS.png", 0, 0, 70, 70);
			SixthBSNS* sixthBSNS = new SixthBSNS("SixthBSNS.png", 0, 0, 70, 70);
			

			setupPosition(firstB, secondBSNS, thirdBSNS, fourthBSNS, fifthBSNS, sixthBSNS, pos);	//Se le ponen la nueva posición a las imágenes

#pragma region uso de random para elegir el tipo de objeto que entrará al nodo

			/*Si random es igual a 1, llama a firstBSNS
			 *Si random es igaul a 2, llama a secondBSNS
			 *Si random es igual a 3, llama a thirdBSNS
			 *Si random es igual a 4, llama a fourthBSNS
			 *Si random es igual a 5, llama a fifthBSNS
			 *Si random es igual a 6, llama a sixthBSNS
			 */
			if(random == 1)
				node = new GraphNode<Texture*>(firstB, position);
			if(random == 2)
				node = new GraphNode<Texture*>(secondBSNS, position);
			if(random == 3)
				node = new GraphNode<Texture*>(thirdBSNS, position);
			if(random == 4)
				node = new GraphNode<Texture*>(fourthBSNS, position);
			if(random == 5)
				node = new GraphNode<Texture*>(fifthBSNS, position);
			if(random == 6)
				node = new GraphNode<Texture*>(sixthBSNS, position);
#pragma endregion
			
			node->index = i * 8 + j; //Los índices de cada nodo incrementarán dependiendo de los ciclos for
			
			gameGraph.InsertNode(i, j, node);
			
			if(j < 7)
				position.x += 70;			
			else
			{
				position.x = 120;
				position.y += 70;
			}
		}
	}

	
	UpdateNodesSons();
}

/*Todos los nodos que existan en el arreglo de nodos de la lista, obrendrán diferentes hijos dependiendo de su posición en la pantalla*/
void GameScreen::UpdateNodesSons()
{
	/*Recorremos entre el arreglo de nodos dentro de la lista del grafo y seleccionamos quien será el hijo de atrás, adelante
	arriba y abajo*/
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(j == 0)
			{
				gameGraph.list->return_at_array(i, j)->prev = nullptr;
			} else
			{
				gameGraph.list->return_at_array(i, j)->prev = gameGraph.list->return_at_array(i, j - 1);	//La posición de atrás será el prev de este nodo
			}
			if(j == 7)
			{
				if( i != 0)
					gameGraph.list->return_at_array(i, j)->bottom = gameGraph.list->return_at_array(i - 1, j);	//La posición de abajo será el bottom de este nodo
				
				if(i != 7)
					gameGraph.list->return_at_array(i, j)->bottom = gameGraph.list->return_at_array(i + 1, j);	//La posición de abajo será el bottom de este nodo
			}
			
			if(i == 0 &&  j < 7)
			{
				
				gameGraph.list->return_at_array(i, j)->bottom = gameGraph.list->return_at_array(i + 1, j);	//La posición de abajo será el bottom de este nodo
				gameGraph.list->return_at_array(i, j)->next = gameGraph.list->return_at_array(i, j+1);	//La posición de enfrente será el next de este nodo
				gameGraph.list->return_at_array(i, j)->top = nullptr; 

			}
			else if(i > 0 &&  j < 7)
			{
				gameGraph.list->return_at_array(i, j)->next = gameGraph.list->return_at_array(i, j + 1); //La posición de enfrente será el next de este nodo
				gameGraph.list->return_at_array(i, j)->bottom = gameGraph.list->return_at_array(i + 1, j);//La posición de abajo será el bottom de este nodo
				gameGraph.list->return_at_array(i, j)->top = gameGraph.list->return_at_array(i - 1, j );	//La posición de arriba será el top de este nodo

			} 
			if(i == 7 &&  j < 7)
			{
				if(j == 0)
					gameGraph.list->return_at_array(i, j)->prev = nullptr;//La posición de atrás será el prev de este nodo
				else
					gameGraph.list->return_at_array(i, j)->prev = gameGraph.list->return_at_array(i, j - 1);	//La posición de atrás será el prev de este nodo

				gameGraph.list->return_at_array(i, j)->next = gameGraph.list->return_at_array(i, j + 1); //La posición de enfrente será el next de este nodo
				gameGraph.list->return_at_array(i, j)->top = gameGraph.list->return_at_array(i - 1, j); //La posición de arriba será el top de este nodo
				gameGraph.list->return_at_array(i, j)->bottom = nullptr;	//La posición de arriba será el top de este nodo

			}

		}
	}	
	gameGraph.list->first = gameGraph.list->graphArr[0][0];
}



/*Llamaremos cada imagen dentro de esta función y a un vector para que con la actualización del vector, seteemos el lugar donde se ubicará la imagen
	@param[firstBSNS] imagen de la primer  empresa
	@param[secondBSNS] imagen de la segunda empresa
	@param[thirdBSNS] imagen de la tercer empresa
	@param[fourthBSNS] imagen de la cuarta empresa
	@param[fifthBSNS] imagen de la quinta empresa
	@param[sixthBSNS] imagen de la sexta empresa
	@param[pos] vector de 2 dimensiones que ubicará a las imágenes dentro de la pantalla*/
void GameScreen::setupPosition(Texture* firstBSNS, Texture* secondBSNS, Texture* thirdBSNS, Texture* fourthBSNS, Texture* fifthBSNS, Texture* sixthBSNS, Vector2 pos)
{
	Texture** textList = new Texture * [6];
	textList[0] = firstBSNS; textList[1] = secondBSNS;textList[2] = thirdBSNS;
	textList[3] = fourthBSNS; textList[4] = fifthBSNS; textList[5] = sixthBSNS;

	//Crea un ciclo for donde cada elemento del arreglo de texturas realiza lo siguiente
	for(int i = 0; i < 6; i++)
	{
		textList[i]->Position(Vector2(pos.x + textList[i]->rect->w/2, -100 + textList[i]->rect->h / 2));	//Se inicializa una posición fuera de la pantalla
		while(textList[i]->Position().y < pos.y + textList[i]->rect->h / 2)	//Mientras sea menor a la posición final indicada, haz un ciclo
		{
			 //Crea un vector con uno en el valor de Y
			textList[i]->addFloat(0, 1);	//Se añade ese valor a Y
			if(textList[i]->Position().y == pos.y + textList[i]->rect->h/2)//Cuando llega a esta posición, termina el while
				break;
		}
	}

}
