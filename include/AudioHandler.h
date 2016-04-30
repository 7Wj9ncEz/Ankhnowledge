q#ifndef AUDIOHANDLER_H_
#define AUDIOHANDLER_H_

#include <iostream>
#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

using namespace std;

class AudioHandler {
	public:
		static AudioHandler* getInstance();
		void update();
		virtual ~AudioHandler();
		void open_audio();
		void set_music(string song);
		void play_music(int times);
		void stopMusic();
		void set_music_volume(int percent);
		void set_effect(string song);
		void play_effect(int times);
		void set_effect_volume(int percent);


	private:
		AudioHandler();
		static AudioHandler *instance;
		Mix_Music *current_music;
		Mix_Chunk *current_effect;
};

#endif
