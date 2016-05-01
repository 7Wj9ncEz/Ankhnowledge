/*
 * SceneTechnology.h
 *
 *  Created on: Oct 7, 2013
 *      Author: makoto
 */

#ifndef SCENETECHNOLOGY_H_
#define SCENETECHNOLOGY_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include <string>

class SceneTechnology : public Scene{
public:
	SceneTechnology(string scene_name);
	virtual ~SceneTechnology();
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
};

#endif /* SCENETECHNOLOGY_H_ */
