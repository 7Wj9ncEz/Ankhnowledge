/*
 * SceneGameOver.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(string sceneName) : Scene (sceneName)  {
	// TODO Auto-generated constructor stub

}

SceneGameOver::~SceneGameOver() {
	// TODO Auto-generated destructor stub
}

void SceneGameOver::Enter()
{
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "lost.png");
	string nextScene = "SceneGameOver" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneGameOver::Exit()
{
	this->cleanGameObjects();
}

