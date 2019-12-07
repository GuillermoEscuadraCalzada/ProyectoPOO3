#include "Graphics.h"

Graphics* Graphics::ptr = NULL;
bool Graphics::initialize = false;


/*Esta funci�n te regresa un apuntador a la clase de Graphics ya que es un Singleton y s�lo necesitamos una instancia de esta clase.*/
Graphics* Graphics::returnPTR()
{
	//Su el apuntador es nulo, crealo
	if(ptr == nullptr)
	{
		ptr = new Graphics();
	} 

	return ptr;
}

/*Al cerrar el juego, manda a llamar esta funci�n donde se borran todas las variables*/
void Graphics::Release()
{
	delete ptr;	//Borra el apuntador
	ptr = nullptr;	//Hazlo nulo
	initialize = false;	//El booleando hazlo falso
}





/*Constructor de la clase graphics*/
Graphics::Graphics()
{
	renderer = nullptr; //Haz nulo el renderer
	initialize = Init();	//Manda a llamar la funci�n de inicializaci�n de esta clase
}

/*Manda a llamar el destructor de la clase*/
Graphics::~Graphics()
{
	
	SDL_DestroyWindow(mainWindow);	//Destruye la ventana de la ventana
	mainWindow = nullptr;	//Haz la ventana nula
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	
	//Cierra todos los programas
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();	//Cierra SDL
}

/*Esta funci�n pregunta si la ventana se hace falsa o verdadera, dependiendo de la respuesta se crea o no la ventana*/
bool Graphics::Init()
{
	//Mensaje que muestra si no se inicializa la ventana
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	} else   //Si logra inicializar, suceder� esto
	{

		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Se crea la ventana de juego con las variables de ancho y altura
		mainWindow = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		//Si no logra crearse, presentar� el siguiente mensaje
		if(mainWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		} else
		{	//Pero si logra crearse, empezar� con el ciclo de render de la ventana

			renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL)
			{
				printf("Renderer Creation Error: %s\n", SDL_GetError());
				return false;
			}

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

			int flags = IMG_INIT_PNG;	//"Bandera" que nos permite determinar si se cargan im�genes o no
			//If que pregunta si se logr� cargar el programa de SDL_Image
			if(!(IMG_Init(flags) & flags))
			{
				printf("IMG initialization ERROR: %s\n", IMG_GetError());
				return false;
			}

			
			if(TTF_Init() == -1)
			{
				printf("TTF ERROR: %s\n", TTF_GetError());
			}

			surface = SDL_GetWindowSurface(mainWindow);
		}


		return true;	//Regresa verdadero
	}
}


/*Funci�n que carga texturas por medio de su direcci�n de su direcci�n en el archivo y se le a�adir� a un vector
	@param[ path ] direccion dentro de la carpeta donde se encuentra el archivo
	@param[ vector ] vector al que se le a�adir� la informaci�n
	@return[texture] una textura que modificar� el surface actual*/
SDL_Texture* Graphics::LoadTexture(std::string path, AssetList<SDL_Texture*>& vector)
{
	SDL_Texture* texture = NULL;	//Empieza en nula 
	SDL_Surface* surface = IMG_Load(path.c_str());	//Esta superficie toma la imagen de este path

	//Si es nulo, manda a llamar ese error
	if(surface == nullptr)
	{
		printf("IMAGE LOAD ERROR: Pat(%s) - Error(%s)\n", path.c_str(), IMG_GetError());	//Error que indica que fall� la carga de imagen
		return texture;
	} else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);	//Se crea una textura gracias a la superficie que carga la imagen.
		vector.push_back(path, texture);	//Se ingresa esta variable hasta atr�s 
		
		//Si la textura es nula, imprime su error
		if(texture == nullptr)
		{
			printf("Create Texture Erro: %sn", SDL_GetError());	//
			return texture;
		}

	}
	SDL_FreeSurface(surface);	//Se libera la superficie actual
	return texture;
}


/*Crea una textura para el texto
	@param[ font ] estilo de la palabras
	@param[text] texto que se quiere imprimir
	@�ram[key] llave que distinguir� a los textos
	@param[ textVector ] vector de textos que almacenar� un nuevo elemento
	@param */
SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, std::string key, 
										 AssetList<SDL_Texture*>& textVector, AssetList<TTF_Font*>& fontVector, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);	//Crea una superficie con el texto indicado, junto a su font y color
	
	//Si la superficie es nula, imprime su error
	if(surface == nullptr)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return nullptr;	//Regresa nu�p
	}
	//En caso contrario
	else
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);	//Crea una textura con la superficie de texto
		textVector.push_back(text, texture);	//A�ade la textura al vector de texturas
		fontVector.push_back(key, font);	//A�ade el font al vector de fonts

		//Si la textura es nula, imprime un error
		if(texture == nullptr)
		{
			printf("Text texture Creation Error: %s\n", SDL_GetError());
			return nullptr;
		}
		SDL_FreeSurface(surface);
		return texture;
	}
}

/*Se limpia el buffer actual*/
void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(renderer);
}

/*Funci�n que manda a llamar las texturas que se creen y se dibujan en la superficie*/
void Graphics::DrawTexture(SDL_Texture* texture,SDL_Rect *clipp, SDL_Rect* rect)
{
	SDL_RenderCopy(renderer, texture, clipp, rect);
}

/*Manda a llamar la funci�n render al momento de crear una nueva ventana*/
void Graphics::Render()
{
	SDL_RenderPresent(renderer); //Actualiza el buffer de la ventana
}