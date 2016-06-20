/*
 * SceneOptions.h
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#ifndef SCENEOPTIONS_H_
#define SCENEOPTIONS_H_
#include "Animation.h"
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include "Slider.h"
#include "OptionsController.h"
#include <string>

class OptionsController;

class SceneOptions : public Scene {
public:
	SceneOptions(string scene_name);
	virtual ~SceneOptions();
	virtual void render(float camera_x, float camera_y);
	virtual int update(int detective);
	void Enter();
	void Exit();

private:
	OptionsController* oc;
	Sprite* sound;
	Animation* soundAnimation;
};

#endif /* SCENEOPTIONS_H_ */
