#include "MenuInicio.h"
TTF_Font* font;
bool undone = false;
MenuInicio::MenuInicio()
{
	std::string path = SDL_GetBasePath();
	path.append("Assets/Fonts/arial.ttf");

	if(TTF_Init() == -1)
	{
		printf("TTF ERROR: %s\n", TTF_GetError());
	}
	font = TTF_OpenFont("C:/Users/Public/Documents/Visual Studio/POO3/Proyecto_POO3/Debug/Assets/Fonts/arial.ttf", 25);

	if(!font )
	{
		
		printf("ERROR: %s\n", TTF_GetError());
		return;
	} else
	{
		SDL_Surface* startSrf = TTF_RenderText_Solid(font, labels[0], color[0]);
		SDL_Surface* exitSrf = TTF_RenderText_Solid(font, labels[1], color[0]);

		Start = SDL_CreateTextureFromSurface(Graphics::returnPTR()->getRender(), startSrf);
		Exit = SDL_CreateTextureFromSurface(Graphics::returnPTR()->getRender(), exitSrf);
		
		SDL_Rect startRect;
		SDL_Rect exitRect;
		int x = 0, y = 0;
		SDL_QueryTexture(Start, nullptr, nullptr, &x, &y);
		SDL_QueryTexture(Exit, nullptr, nullptr, &x, &y);
		int wdth = Graphics::returnPTR()->SCREEN_WIDTH / 2;
		int height = Graphics::returnPTR()->SCREEN_HEIGHT / 2;
		startRect = { wdth - startSrf->clip_rect.w / 2, height - 20 , x, y };
		exitRect = { wdth - exitSrf->clip_rect.w / 2, height + 20, x, y };

		menu[0] = startSrf;
		menu[1] = exitSrf;

		pos[0] = startRect;
		pos[1] = exitRect;

		SDL_FreeSurface(startSrf);
		SDL_FreeSurface(exitSrf);
		SDL_RenderClear(Graphics::returnPTR()->getRender());
		SDL_RenderCopy(Graphics::returnPTR()->getRender(), Start, nullptr, &startRect);
		SDL_RenderCopy(Graphics::returnPTR()->getRender(), Exit, nullptr, &exitRect);
		SDL_RenderPresent(Graphics::returnPTR()->getRender());
	}


}



MenuInicio::~MenuInicio()
{
	TTF_CloseFont(font);

}

void MenuInicio::Update()
{
	while(!undone)
	{
		while(SDL_PollEvent(&eventHandler) != 0)
		{
			switch(eventHandler.type)
			{
			case SDL_QUIT:
				for(int i = 0; i < 2; i++)
					SDL_FreeSurface(menu[i]);
				break;

			
			case SDL_MOUSEMOTION: //El mouse se encuentra encima de las letras
			{
				x = eventHandler.motion.x;
				y = eventHandler.motion.y;

				for(int i = 0; i < 2; i++)
				{
					if(x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if(!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menu[i]);
							menu[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					} else
					{
						if(selected[i])
						{
							selected[i] = 0;
							SDL_FreeSurface(menu[i]);
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
				for(int i = 0; i < 2; i++)
				{
					if(x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if(i == 0)
						{

							printf("Start pressed\n");
							SDL_FreeSurface(menu[0]);
						} else
						{
							printf("Exit pressed\n");
							SDL_FreeSurface(menu[1]);
						}

					}
				}
				break;
			}
				

			case SDL_KEYDOWN:
				if(eventHandler.key.keysym.sym == SDLK_ESCAPE)
				{
					for(int i = 0; i < 2; i++)
						SDL_FreeSurface(menu[i]);
				}
				break;
			}
		}
	}
	
}

void MenuInicio::Render()
{
}
