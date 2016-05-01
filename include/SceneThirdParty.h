/*
 * SceneThirdParty.h
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#ifndef SCENETHIRDPARTY_H_
#define SCENETHIRDPARTY_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include <string>

class SceneThirdParty : public Scene{
public:
	SceneThirdParty(string scene_name);
	virtual ~SceneThirdParty();
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
};

#endif /* SCENETHIRDPARTY_H_ */
