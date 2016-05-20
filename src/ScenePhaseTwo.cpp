/*
 * ScenePhaseTwo.cpp
 *
 * Responsible for changing the game phase to the one number "two"
 */

#include "ScenePhaseTwo.h"
#include "AudioHandler.h"

ScenePhaseTwo::ScenePhaseTwo(string scene_name) : Scene (scene_name) {


}

ScenePhaseTwo::~ScenePhaseTwo() {
	// TODO Auto-generated destructor stub
}

/**
 * Changes the game scene to the phase two
**/
void ScenePhaseTwo::Enter() {
	AudioHandler * audio = AudioHandler::getInstance();
	audio->stopMusic();
	audio->set_music("fase2.ogg");
	audio->play_music(-1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "interface.png");
	this->tile = new Sprite(SDLBase::resourcesPath + "tile.png");
	this->block = new Sprite(SDLBase::resourcesPath + "areiamovedicabloco.png");
	this->map = new Map(tile, block, SDLBase::resourcesPath +"tileMap2.txt", 200, 100);
	string nextScene = "ScenePhaseTwo" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	this->addGameObject(map);
	GameManager::fade_screen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "ScenePhaseTwo"
**/
void ScenePhaseTwo::Exit() {
	this->clean_game_objects();
}
