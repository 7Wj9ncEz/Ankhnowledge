/*
 * ScenePhaseThree.h
 *
 *  Created on: Nov 26, 2013
 *      Author: makoto
 */

#ifndef SCENEPHASETHREE_H_
#define SCENEPHASETHREE_H_


#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "Character.h"
#include "GameObject.h"
#include "Map.h"
#include <string>

class ScenePhaseThree  : public Scene{
public:
	ScenePhaseThree(string scene_name);
	virtual ~ScenePhaseThree();
	void Enter();
	void Exit();
private:
	Sprite * splashSprite,*charSprite, *tile, *block;
	GameObject *map;
};

#endif /* SCENEPHASETHREE_H_ */
