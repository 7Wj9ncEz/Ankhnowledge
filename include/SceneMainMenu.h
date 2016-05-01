/*
 * SceneMainMenu.h
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#ifndef SCENEMAINMENU_H_
#define SCENEMAINMENU_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "MainMenuButHandler.h"
#include "GameObject.h"
#include <string>

class SceneMainMenu : public Scene{
public:
	SceneMainMenu (string scene_name);
	virtual ~SceneMainMenu ();
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
	GameObject* buttons,*bg;
};

#endif /* SCENEMAINMENU_H_ */
