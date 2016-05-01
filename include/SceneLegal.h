/*
 * SceneLegal.h
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#ifndef SCENELEGAL_H_
#define SCENELEGAL_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include <string>

class SceneLegal : public Scene {
public:
	SceneLegal(string scene_name);
	virtual ~SceneLegal();
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
};

#endif /* SCENELEGAL_H_ */
