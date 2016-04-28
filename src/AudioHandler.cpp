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
	this->current_music = NULL;
	this->current_effect = NULL;
	open_audio();
}

AudioHandler::~AudioHandler()  {
	Mix_FreeMusic(current_music);
	Mix_CloseAudio();
	Mix_Quit();
	if(this->current_music)
		Mix_FreeMusic(this->current_music);
	if(this->current_effect)
		Mix_FreeChunk(this->current_effect);
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

void AudioHandler::open_audio() {
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

void AudioHandler::set_music(string song) {
	if (this->current_music) {
		Mix_FreeMusic(this->current_music);
	}

	else {
		// Nothing to do
	}

	string songPath = SDLBase::resourcesPath + song;

	this->current_music = Mix_LoadMUS(songPath.c_str());
}

void AudioHandler::play_music(int times) {
	if (this->current_music)	{
		Mix_PlayMusic(this->current_music, times);

		//Mix_HookMusicFinished(cleanMusic);
	}

	else {
		cout << "There is no song loaded" << endl;
	}
}

void AudioHandler::stopMusic() {
	Mix_HaltMusic();
}

void AudioHandler::set_music_volume(int percent) {
	int value = percent * MIX_MAX_VOLUME/100;
	Mix_VolumeMusic(value);
}

void AudioHandler::set_effect(string song) {
	if (this->current_effect) {
		Mix_FreeChunk(this->current_effect);
	}

	else {
		// Nothing to do
	}

	string songPath = SDLBase::resourcesPath + song;
	this->current_effect = Mix_LoadWAV(songPath.c_str());
}

void AudioHandler::play_effect(int times) {
	if (this->current_effect) {
		Mix_PlayChannel(1, this->current_effect, times);

		//Mix_HookMusicFinished(cleanMusic);
	}

	else {
		cout << "There is no song loaded" << endl;
	}
}

void AudioHandler::set_effect_volume(int percent) {
	int value = percent * MIX_MAX_VOLUME/100;
	Mix_Volume(1, value);
}
