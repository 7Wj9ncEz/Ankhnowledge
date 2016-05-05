/*
 * SceneTechnology.cpp
 *
 * Scene responsible for showing the user the Technology map
 */

#include "SceneTechnology.h"

SceneTechnology::SceneTechnology(string scene_name) : Scene (scene_name) {

}

SceneTechnology::~SceneTechnology() {
}

/**
 * Changes the game scene the technology map
**/
void SceneTechnology::Enter()
{
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "splashtechnology.png");
	string nextScene = "SceneThirdParty" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "SceneTechnology"
**/
void SceneTechnology::Exit()
{
	this->clean_game_objects();
}
