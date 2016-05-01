/*
 * SceneThirdParty.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#include "SceneThirdParty.h"

SceneThirdParty::SceneThirdParty(string scene_name) : Scene (scene_name) {

}

SceneThirdParty::~SceneThirdParty() {
}

void SceneThirdParty::Enter()
{
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "splashthirdparty.png");
	string nextScene = "SceneLegal" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneThirdParty::Exit()
{
	this->clean_game_objects();
}

