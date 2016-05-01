/*
 * ScenePhaseTwo.h
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#ifndef SCENEPHASETWO_H_
#define SCENEPHASETWO_H_

#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "Character.h"
#include "GameObject.h"
#include "Map.h"
#include <string>

class ScenePhaseTwo : public Scene{
public:
	ScenePhaseTwo (string scene_name);
	virtual ~ScenePhaseTwo ();
	void Enter();
	void Exit();
private:
	Sprite * splashSprite,*charSprite, *tile, *block;
	GameObject *map;
};

#endif /* SCENEPHASETWO_H_ */
