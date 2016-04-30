/*
 * SceneLegal.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#include "SceneLegal.h"

SceneLegal::SceneLegal(string sceneName) : Scene (sceneName) {

}

SceneLegal::~SceneLegal() {
}

void SceneLegal::Enter()
{
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "splashlegal.png");
	string nextScene = "SceneMainMenu" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneLegal::Exit()
{
	this->cleanGameObjects();
}

