#include "Graphics.h"

Graphics* Graphics::ptr = NULL;
bool Graphics::initialize = false;


/*Esta función te regresa un apuntador a la clase de Graphics ya que es un Singleton y sólo necesitamos una instancia de esta clase.*/
Graphics* Graphics::returnPTR()
{
	//Su el apuntador es nulo, crealo
	if(ptr == nullptr)
	{
		ptr = new Graphics();
	} 

	return ptr;
}

/*Al cerrar el juego, manda a llamar esta función donde se borran todas las variables*/
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
	initialize = Init();	//Manda a llamar la función de inicialización de esta clase
}

/*Manda a llamar el destructor de la clase*/
Graphics::~Graphics()
{
	
	SDL_DestroyWindow(mainWindow);	//Destruye la ventana de la ventana
	mainWindow = nullptr;	//Haz la ventana nula
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();	//Cierra SDL
}

/*Esta función pregunta si la ventana se hace falsa o verdadera, dependiendo de la respuesta se crea o no la ventana*/
bool Graphics::Init()
{
	//Mensaje que muestra si no se inicializa la ventana
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	} else   //Si logra inicializar, sucederá esto
	{

		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Se crea la ventana de juego con las variables de ancho y altura
		mainWindow = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		//Si no logra crearse, presentará el siguiente mensaje
		if(mainWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		} else
		{	//Pero si logra crearse, empezaré con el ciclo de render de la ventana

			renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL)
			{
				printf("Renderer Creation Error: %s\n", SDL_GetError());
				return false;
			}

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

			int flags = IMG_INIT_PNG;	//"Bandera" que nos permite determinar si se cargan imágenes o no
			//If que pregunta si se logró cargar el programa de SDL_Image
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


/*Función que carga texturas por medio de su dirección de su dirección en el archivo y se le añadirá a un vector
	@param[ path ] direccion dentro de la carpeta donde se encuentra el archivo
	@param[ vector ] vector al que se le añadirá la información
	@return[texture] una textura que modificará el surface actual*/
SDL_Texture* Graphics::LoadTexture(std::string path, Vector<std::string>& vector)
{
	SDL_Texture* texture = NULL;	//Empieza en nula 
	SDL_Surface* surface = IMG_Load(path.c_str());	//Esta superficie toma la imagen de este path

	//Si es nulo, manda a llamar ese error
	if(surface == nullptr)
	{
		printf("IMAGE LOAD ERROR: Pat(%s) - Error(%s)\n", path.c_str(), IMG_GetError());	//Error que indica que falló la carga de imagen
		return texture;
	} else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		vector.push_back_texture(path, texture);
		if(texture == nullptr)
		{
			printf("Create Texture Erro: %sn", SDL_GetError());
			return texture;
		}

	}
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 0,0,0 });
	if(surface == nullptr)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return nullptr;
	}
	else
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		
		if(texture == nullptr)
		{
			printf("Text texture Creation Error: %s\n", SDL_GetError());
			return nullptr;
		}
		SDL_FreeSurface(surface);
		return texture;
	}
}


void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(renderer);
}

/*Función que manda a llamar las texturas que se creen*/
void Graphics::DrawTexture(SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

/*Manda a llamar la función render al momento de crear una nueva ventana*/
void Graphics::Render()
{
	SDL_RenderPresent(renderer); //Actualiza el buffer de la ventana
}