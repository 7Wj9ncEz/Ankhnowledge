/*
 * SplashScreen.h
 *
 *  Created on: Oct 7, 2013
 *      Author: makoto
 */

#ifndef SPLASHSCREEN_H_
#define SPLASHSCREEN_H_
#include "GameObject.h"
#include "Sprite.h"
#include "SDLBase.h"
#include "GameManager.h"
#include <string>

class SplashScreen : public GameObject{
public:
	SplashScreen(Sprite * sprite, string nextScene);
	virtual ~SplashScreen();
	int update(int user_input_checker);
	void render(float camera_x, float camera_y);

private:
	Sprite * sprite;
	int initialTime;
	bool activated;
	string nextScene;
};

#endif /* SPLASHSCREEN_H_ */
