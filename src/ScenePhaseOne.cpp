/*
 * ScenePhaseOne.cpp
 *
 * Responsible for changing the game phase to the one number "one"
 */

#include "ScenePhaseOne.h"
#include "AudioHandler.h"

ScenePhaseOne::ScenePhaseOne(string scene_name) : Scene (scene_name) {


}

ScenePhaseOne::~ScenePhaseOne() {
	// TODO Auto-generated destructor stub
}

/**
 * Changes the game scene to the phase one
**/
void ScenePhaseOne::Enter() {
	AudioHandler * audio = AudioHandler::getInstance();
	audio->stopMusic();
	audio->set_music("fase1.ogg");
	audio->play_music(-1);

	this->splashSprite = new Sprite(SDLBase::resourcesPath + "interface.png");
	this->tile = new Sprite(SDLBase::resourcesPath + "tile.png");
	this->block = new Sprite(SDLBase::resourcesPath + "areiamovedicabloco.png");
	this->map = new Map(tile, block, SDLBase::resourcesPath +"tileMap.txt", 200, 100);
	string nextScene = "ScenePhaseOne" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	this->addGameObject(map);
	GameManager::fadeScreen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "ScenePhaseOne"
**/
void ScenePhaseOne::Exit() {
	this->clean_game_objects();
}
