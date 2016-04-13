/*
 * SplashScreen.cpp
 *
 *  Created on: Oct 7, 2013
 *      Author: makoto
 */

#include "SplashScreen.h"
#include <iostream>
using namespace std;

SplashScreen::SplashScreen(Sprite * sprite, string nextScene): GameObject(0,0) {
	this->sprite = sprite;
	initialTime = SDLBase::getTime();
	this->activated = false;
	this->nextScene = nextScene;
}

SplashScreen::~SplashScreen() {
	delete sprite;
}

int SplashScreen::update(int dt) {

	if ((SDLBase::getTime() - initialTime > 5000) && !activated) {
		activated = true;
		if(GameManager::currentScene->changeScene(nextScene) == 1) {
			GameManager::fadeScreen->fadeIn(1,2);
		}

		else {
			// Nothing to do
		}
	}

	else {
		// Nothing to do
	}

	return 0;
}

void SplashScreen::render(float cameraX, float cameraY) {
	if(sprite) {
			this->sprite->render(0,0);
	}

	else {
		// Nothing to do
	}
}
