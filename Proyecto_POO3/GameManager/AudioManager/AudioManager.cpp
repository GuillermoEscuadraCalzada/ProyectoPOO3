#include "AudioManager.h"
AudioManager* AudioManager::ptr = nullptr;

/*Constructor por defecto de la clase Audio Manager*/
AudioManager::AudioManager()
{
	assetMNGR = AssetManager::getPTR();	//Se crea un apuntador de esta clase

	//Si el audio falla, imprime un error
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("Mixer Initialization Error: %s\n", Mix_GetError());
	}
}

/*Destructor por defecto de la clase AudioManager*/
AudioManager::~AudioManager()
{
	assetMNGR = nullptr;
	Mix_Quit();	//Se cierra la librear�a de Mixer
}

/*Funci�n que crear� el apuntador de esta clase*/
AudioManager* AudioManager::getPTR()
{
	//Si apuntador es nulo, crea una nueva clase AudioManager
	if(ptr == nullptr)
	{
		ptr = new AudioManager();
	}

	return ptr;	//Regresa el apuntador
}

/*Release eliminar� el apuntador y lo har� nulo*/
void AudioManager::Release()
{
	delete ptr;
	ptr = nullptr;
}

/*Play music se encargar� de reproducir la m�sica por las veces que se indique
	@param[fileName] nombre del audio
	@param[loops] n�mero de veces que se quiere repetir (1 o infinitas)*/
void AudioManager::PlayMusic(string fileName, int loops)
{
	Mix_PlayMusic(assetMNGR->GetMusic(fileName), loops);
}

/*Esta funci�n se encargar� de pausar la m�sica*/
void AudioManager::PauseMusic()
{
	if(Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

/*Funci�n que se encargar� de continuar con la m�sica en el momento que se qued� pausada*/
void AudioManager::ResumeMusic()
{
	if(Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

/*PlaySFX es una funci�n que reproducir� una vez o muchas veces un sfx
	@param[fileName] nombre del sfx
	@param[loops] numero de veces que se repetir� el sfx
	@param[channel] "canal" donde se quiere que suene el sfx*/
void AudioManager::PlaySFX(string fileName, int loops, int channel)
{
	Mix_PlayChannel(channel, assetMNGR->GetSFX(fileName), loops);
}
