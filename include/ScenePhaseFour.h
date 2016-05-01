/*
 * ScenePhaseFour.h
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#ifndef SCENEPHASEFOUR_H_
#define SCENEPHASEFOUR_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "Character.h"
#include "GameObject.h"
#include "Map.h"
#include <string>

class ScenePhaseFour : public Scene{
public:
	ScenePhaseFour(string scene_name);
	virtual ~ScenePhaseFour();
	void Enter();
	void Exit();
private:
	Sprite * splashSprite,*charSprite, *tile, *block;
	GameObject *map;
};

#endif /* SCENEPHASEFOUR_H_ */
