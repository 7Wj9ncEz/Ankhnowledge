/*
 * ScenePhaseOne.h
 *
 *  Created on: Oct 8, 2013
 *      Author: al
 */

#ifndef SCENEPHASEONE_H_
#define SCENEPHASEONE_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "Character.h"
#include "GameObject.h"
#include "Map.h"
#include <string>

class ScenePhaseOne : public Scene{
public:
	ScenePhaseOne(string scene_name);
	virtual ~ScenePhaseOne();
	void Enter();
	void Exit();
private:
	Sprite * splashSprite,*charSprite, *tile, *block;
	GameObject *map;
};

#endif /* SCENEPHASEONE_H_ */
