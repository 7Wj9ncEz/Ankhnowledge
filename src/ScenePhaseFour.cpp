/*
 * ScenePhaseFour.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#include "ScenePhaseFour.h"
#include "AudioHandler.h"

ScenePhaseFour::ScenePhaseFour(string sceneName) : Scene (sceneName) {


}

ScenePhaseFour::~ScenePhaseFour() {
	// TODO Auto-generated destructor stub
}

void ScenePhaseFour::Enter()
{
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

void ScenePhaseFour::Exit()
{
	this->cleanGameObjects();
}

