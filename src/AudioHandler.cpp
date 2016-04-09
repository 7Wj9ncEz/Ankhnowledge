#include <iostream>
#include <string>

#include "SDL/SDL_mixer.h"

#include "AudioHandler.h"
#include "SDLBase.h"
#include "Scene.h"

using namespace std;

void cleanMusic();

AudioHandler * AudioHandler::instance = 0;

AudioHandler::AudioHandler() {
	this->currentMusic = NULL;
	this->currentEffect = NULL;
	openAudio();
}

AudioHandler::~AudioHandler()  {
	Mix_FreeMusic(currentMusic);
	Mix_CloseAudio();
	Mix_Quit();
	if(this->currentMusic)
		Mix_FreeMusic(this->currentMusic);
	if(this->currentEffect)
		Mix_FreeChunk(this->currentEffect);
}

void AudioHandler::update(){
	// Nothing to do
}

AudioHandler * AudioHandler::getInstance() {
	if (!instance){
		instance = new AudioHandler();
	}

	else {
		// Nothing to do
	}

	return instance;
}

void AudioHandler::openAudio() {
	int audio_rate = 44100;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
	    cout << "Unable to open audio: " << Mix_GetError() << endl;
	    exit(1);
	}

	else {
		// Nothing to do
	}
}

void AudioHandler::setMusic(string song) {
	if (this->currentMusic) {
		Mix_FreeMusic(this->currentMusic);
	}

	else {
		// Nothing to do
	}

	string songPath = SDLBase::resourcesPath + song;

	this->currentMusic = Mix_LoadMUS(songPath.c_str());
}

void AudioHandler::playMusic(int times) {
	if (this->currentMusic)	{
		Mix_PlayMusic(this->currentMusic, times);

		//Mix_HookMusicFinished(cleanMusic);
	}

	else {
		cout << "There is no song loaded" << endl;
	}
}

void AudioHandler::stopMusic() {
	Mix_HaltMusic();
}

void AudioHandler::setMusicVolume(int percent) {
	int value = percent * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);
}

void AudioHandler::setEffect(string song) {
	if (this->currentEffect) {
		Mix_FreeChunk(this->currentEffect);
	}

	else {
		// Nothing to do
	}

	string songPath = SDLBase::resourcesPath + song;
	this->currentEffect = Mix_LoadWAV(songPath.c_str());
}

void AudioHandler::playEffect(int times) {
	if (this->currentEffect) {
		Mix_PlayChannel(1, this->currentEffect, times);

		//Mix_HookMusicFinished(cleanMusic);
	}

	else {
		cout << "There is no song loaded" << endl;
	}
}

void AudioHandler::setEffectVolume(int percent) {
	int value = percent * MIX_MAX_VOLUME/100;
	Mix_Volume(1, value);
}
