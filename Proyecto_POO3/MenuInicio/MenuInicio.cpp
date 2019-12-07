#include "MenuInicio.h"


/*Ayuda obtenida de: https://pastebin.com/Ve3CXyMe */

TTF_Font* font;
const char* labels[3] = { "Start", "High Score", "Exit"};
SDL_Surface* arr[3];
bool undone = false;
void MenuInicio::Init()
{
	int width = Graphics::returnPTR()->SCREEN_WIDTH / 2;		//Tamaños de la ventana
	int height = Graphics::returnPTR()->SCREEN_HEIGHT / 2;	//Tamaños de la ventana
	text = new Texture("Fondo.png", 0, 0, 600,600);
	text->Position(Vector2(300, 300));
#pragma region RenderTextSolid
	//Se crean las superficies con el texto indicado y el color[0]
	arr[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	arr[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	arr[2] = TTF_RenderText_Solid(font, labels[2], color[0]);
	title = TTF_RenderText_Solid(font, "Match 3: Food Edition", color[0]);
#pragma endregion

#pragma region	Creación de superficies
	//Las texturas toman las superficies para poder crearse 
	Start = SDL_CreateTextureFromSurface(render, arr[0]);
	hScore = SDL_CreateTextureFromSurface(render, arr[1]);
	Exit = SDL_CreateTextureFromSurface(render, arr[2]);
	Title = SDL_CreateTextureFromSurface(render, title);
#pragma endregion



	SDL_Rect startRect, exitRect, titleRect, highScr;		//Se crean las superficies donde se dibujarán los textos
	int x = 0, y = 0;
	int titleX = 0, titleY = 0;
	int highScoreX = 0, highScoreY = 0;
	int exitX = 0, exitY = 0;

#pragma region QueryTexture
	SDL_QueryTexture(Start, nullptr, nullptr, &x, &y);	//Se adaptan las texturas al tamaño del string 
	SDL_QueryTexture(Exit, nullptr, nullptr, &exitX, &exitY);	//Se adaptan las texturas al tamaño del string 
	SDL_QueryTexture(hScore, nullptr, nullptr, &highScoreX, &highScoreY);	//Se adaptan las texturas al tamaño del string 
	SDL_QueryTexture(Title, nullptr, nullptr, &titleX, &titleY);
#pragma endregion

#pragma region Rects Setup
	startRect = { width - arr[0]->clip_rect.w / 2, height - 20, x, y };										//Su ubican correctamente los textos
	highScr = { width - arr[2]->clip_rect.w / 2, height + 40, highScoreX, highScoreY };											//Su ubican correctamente los textos
	exitRect = { width - arr[1]->clip_rect.w / 4, height + 80, exitX, exitY };		//Su ubican correctamente los textos
	titleRect = { width - title->clip_rect.w / 2, 0 + 20, titleX, titleY };
#pragma endregion
	


	for(int i = 0; i < 3; i++)
		menu[i] = arr[i];


	pos[0] = startRect;	//Estos índices toman estos Rect
	pos[1] = highScr;
	pos[2] = exitRect;	//Estos índices toman estos Rect
	pos[3] = titleRect;

	/*El render se actualiza y obtiene la información que se cargó en este lugar.*/
	changeRender();
}


MenuInicio::MenuInicio()
{
	x = y = 0;

	//Se busca el font indicado por medio de su ubicación general en el archivo
	std::string path = SDL_GetBasePath();
	path.append("Assets/Fonts/arial.ttf");

	/*Se inicializa ttf_init porque si no el font no puede funcionar.*/
	if(TTF_Init() == -1)
	{
		printf("TTF ERROR: %s\n", TTF_GetError());	//Imprime su error si no se encuentra
	}
	font = TTF_OpenFont("C:/Users/Public/Documents/Visual Studio/POO3/Proyecto_POO3/Debug/Assets/Fonts/arial.ttf", 25);

	/*Si font es nulo, imprime su error y regresa*/
	if(!font )
	{
		
		printf("ERROR: %s\n", TTF_GetError());
		return;
	} 
	else
	{	//Si no es nula, haz lo siguiente
		
		Init();
	}
	printf("Menu initialized\n");

}


/*Destructor de la clase menu de inicio*/
MenuInicio::~MenuInicio()
{


	TTF_CloseFont(font);	//Se cierra la librería font

}

void MenuInicio::Update()
 {
	//Mientras no esté terminado el menú, realiza lo siguiente
	while(!undone)
	{
		//Espera entre los eventos de SDL
		while(SDL_PollEvent(&eventHandler))
		{
			//Si undone es falso, cambia el render por lo que se deba de cambiar
			if(!undone)
			{
				//Las  texturas actualizan su respectiva información y modifican el render actual
				changeRender();
			}
			switch(eventHandler.type)
			{//Cambia entre los eventos de SDL

				//Si es SDL_QUIT, borra todas las surfaces
			case SDL_QUIT:
				undone = true;
				continuee = false;
				for(int i = 0; i < 3; i++)
					SDL_FreeSurface(menu[i]);
				SDL_FreeSurface(title);
				break;

			
			case SDL_MOUSEMOTION: //El mouse se encuentra encima de las letras
			{
				//Obten los valores del mouse
				x = eventHandler.motion.x;
				y = eventHandler.motion.y;

				//Pregunta constantemente entre los 
				for(int i = 0; i < 3; i++)
				{
					//Pregunta si el mouse se encuentra dentro de la caja de texto
					if(x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						//Si esta posición es falsa
						if(!selected[i])
						{
							//Hazla verdadera
							selected[i] = 1;
							SDL_FreeSurface(menu[i]);	//Libera la imagen
							menu[i] = TTF_RenderText_Solid(font, labels[i], color[1]);	//Cambiala por el mismo texto y con un color diferente
						}
					}
					else
					{
						//Si ya es verdadero
						if(selected[i])
						{
							//Cambialo a falso
							selected[i] = 0;
							SDL_FreeSurface(menu[i]);	//Libera 
							menu[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
						}
					}
				}
				break;
			}
				
			case SDL_MOUSEBUTTONDOWN:	//El botón izquierdo del mouse fue presionado
			{
				x = eventHandler.button.x;  //Detecta la posi´ción del mouse en X
				y = eventHandler.button.y;	//Detecta la posi´ción del mouse en Y
				for(int i = 0; i < 3; i++)
				{
					//Si el mouse se encuentra dentro de la caja de texto y el mouse es presionado
					if(x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						//Pregunta si i es igual a 1
						if(i == 2)
						{
							//Haz falso los dos booleanos
							printf("Button pressed\n");
							undone = true;
							continuee = false;
							//Libera las superficies
							for(int i = 0; i < 3; i++)
								SDL_FreeSurface(menu[i]);

						} 
						//Si no, sólo haz undone falso
						else if(i == 0)
							undone = true;

					}
				}
				break;
			}
				

			case SDL_KEYDOWN:
			{
				if(eventHandler.key.keysym.sym == SDLK_ESCAPE)
				{
					printf("exit key pressed\n");
					undone = true;
					for(int i = 0; i < 3; i++)
						SDL_FreeSurface(menu[i]);
				}
				break;
			}
			}
		}
		
	}
	
}

/*Change Render buscará cambiar el render actual, actualizando las texturas y haciendo que el render general muestre las texturas del menú.*/
void MenuInicio::changeRender()
{
	SDL_RenderClear(render);
	Start = SDL_CreateTextureFromSurface(render, menu[0]);
	hScore = SDL_CreateTextureFromSurface(render, menu[1]);
	Exit = SDL_CreateTextureFromSurface(render, menu[2]);
	Title = SDL_CreateTextureFromSurface(render, title);

	//Se borra el render actual
	if(text != nullptr)
		text->Render();
	SDL_RenderCopy(render, Start, nullptr, &pos[0]);
	SDL_RenderCopy(render, hScore, nullptr, &pos[1]);
	SDL_RenderCopy(render, Exit, nullptr, &pos[2]);
	SDL_RenderCopy(render, Title, nullptr, &pos[3]);
	
	SDL_RenderPresent(render);
}
