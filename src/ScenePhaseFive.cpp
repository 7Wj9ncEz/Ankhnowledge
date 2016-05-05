/*
 * ScenePhaseFive.cpp
 *
 * Responsible for changing the game phase to the one number "five"
 */

#include "ScenePhaseFive.h"
#include "AudioHandler.h"

ScenePhaseFive::ScenePhaseFive(string scene_name) : Scene (scene_name) {


}

ScenePhaseFive::~ScenePhaseFive() {
	// TODO Auto-generated destructor stub
}

/**
 * Changes the game scene to the phase five
**/
void ScenePhaseFive::Enter() {
	AudioHandler * audio = AudioHandler::getInstance();
	audio->stopMusic();
	audio->set_music("fase5.ogg");
	audio->play_music(-1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "interface.png");
	this->tile = new Sprite(SDLBase::resourcesPath + "tile.png");
	this->block = new Sprite(SDLBase::resourcesPath + "areiamovedicabloco.png");
	this->map = new Map(tile, block, SDLBase::resourcesPath +"tileMap5.txt", 200, 100);
	string nextScene = "ScenePhaseFive" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	this->addGameObject(map);
	GameManager::fadeScreen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "ScenePhaseFive"
**/
void ScenePhaseFive::Exit() {
	this->clean_game_objects();
}
