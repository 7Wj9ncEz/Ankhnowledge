/*
 * ScenePhaseFour.cpp
 *
 * Responsible for changing the game phase to the one number "four"
 */

#include "ScenePhaseFour.h"
#include "AudioHandler.h"

ScenePhaseFour::ScenePhaseFour(string scene_name) : Scene (scene_name) {


}

ScenePhaseFour::~ScenePhaseFour() {
	// TODO Auto-generated destructor stub
}

/**
 * Changes the game scene to the phhase four
**/
void ScenePhaseFour::Enter() {
	AudioHandler * audio = AudioHandler::getInstance();
	audio->stopMusic();
	audio->set_music("fase4.ogg");
	audio->play_music(-1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "interface.png");
	this->tile = new Sprite(SDLBase::resourcesPath + "tile.png");
	this->block = new Sprite(SDLBase::resourcesPath + "areiamovedicabloco.png");
	this->map = new Map(tile, block, SDLBase::resourcesPath +"tileMap4.txt", 200, 100);
	string nextScene = "ScenePhaseFour" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	this->addGameObject(map);
	GameManager::fadeScreen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "ScenePhaseFour"
**/
void ScenePhaseFour::Exit() {
	this->clean_game_objects();
}
