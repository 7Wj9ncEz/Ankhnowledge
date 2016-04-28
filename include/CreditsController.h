/*
 * OptionsController.h
 *
 *  Created on: Oct 29, 2013
 *      Author: al
 */

#ifndef CREDITSCONTROLLER_H_
#define CREDITSCONTROLLER_H_
#include "GameObject.h"
#include "Button.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Sprite.h"
#include <string>

using namespace std;

class CreditsController:public GameObject {
public:
	CreditsController();
	virtual ~CreditsController();
	void render(float camera_x, float camera_y);
	int update(int dt);
	void mouseOver(Button* bt);
	void mousePressed(Button* bt,string nextScene);
	void changeScene(string nextScene);

private:
	InputManager* input;
	Button *back;
	Sprite *back_1,*back_2,*back_3,*splashSprite;
};

#endif /* OPTIONSCONTROLLER_H_ */
