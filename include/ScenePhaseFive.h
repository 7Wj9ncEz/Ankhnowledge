/*
 * ScenePhaseFive.h
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#ifndef SCENEPHASEFIVE_H_
#define SCENEPHASEFIVE_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "Character.h"
#include "GameObject.h"
#include "Map.h"
#include <string>

class ScenePhaseFive : public Scene{
public:
	ScenePhaseFive(string scene_name);
	virtual ~ScenePhaseFive();
	void Enter();
	void Exit();
private:
	Sprite * splashSprite,*charSprite, *tile, *block;
	GameObject *map;
};

#endif /* SCENEPHASEFIVE_H_ */
