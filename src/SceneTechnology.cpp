/*
 * SceneTechnology.cpp
 *
 *  Created on: Oct 7, 2013
 *      Author: makoto
 */

#include "SceneTechnology.h"

SceneTechnology::SceneTechnology(string sceneName) : Scene (sceneName) {

}

SceneTechnology::~SceneTechnology() {
}

void SceneTechnology::Enter()
{
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "splashtechnology.png");
	string nextScene = "SceneThirdParty" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneTechnology::Exit()
{
	this->cleanGameObjects();
}

