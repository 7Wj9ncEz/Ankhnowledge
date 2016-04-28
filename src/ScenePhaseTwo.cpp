/*
 * ScenePhaseTwo.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#include "ScenePhaseTwo.h"
#include "AudioHandler.h"

ScenePhaseTwo::ScenePhaseTwo(string sceneName) : Scene (sceneName) {


}

ScenePhaseTwo::~ScenePhaseTwo() {
	// TODO Auto-generated destructor stub
}

void ScenePhaseTwo::Enter()
{
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
	GameManager::fadeScreen->fadeOut(0,2);
}

void ScenePhaseTwo::Exit()
{
	this->cleanGameObjects();
}

