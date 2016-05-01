/*
 * SceneGameOver.h
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#ifndef SCENEGAMEOVER_H_
#define SCENEGAMEOVER_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include <string>


class SceneGameOver : public Scene {
public:
	SceneGameOver(string scene_name);
	virtual ~SceneGameOver();
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
};

#endif /* SCENEGAMEOVER_H_ */
