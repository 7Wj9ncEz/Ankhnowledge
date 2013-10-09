/*
 * SceneMainMenu.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu(string sceneName) : Scene (sceneName) {

}

SceneMainMenu::~SceneMainMenu() {
}

void SceneMainMenu::Enter()
{
	this->splashSprite = new Sprite("../Ankhnowledge/resources/images/splashmainmenu.png");
	string nextScene = "ScenePhaseOne" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fadeOut(0,2);
}

void SceneMainMenu::Exit()
{
	this->cleanGameObjects();
}

