/*
 * SceneLegal.cpp
 *
 * Classes that creates the "LegalScene" for the user
 */

#include "SceneLegal.h"

SceneLegal::SceneLegal(string scene_name) : Scene (scene_name) {

}

SceneLegal::~SceneLegal() {
}

/**
 * Shows on the screen the LegalScene with it's sprites
**/
void SceneLegal::Enter() {
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "splashlegal.png");
	string nextScene = "SceneMainMenu" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fade_out(0,2);
}

/**
 * Cleans all the objects in the "Legal Scene"
**/
void SceneLegal::Exit() {
	this->clean_game_objects();
}
