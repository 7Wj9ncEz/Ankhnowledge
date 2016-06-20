/*
 * Slider.h
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#ifndef SLIDER_H_
#define SLIDER_H_
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include <iostream>

class Slider:public GameObject {
public:
	Slider(Sprite* button, Sprite* slider, float x, float y);
	virtual ~Slider();
	void render(float camera_x, float camera_y);
	int update(int detective);
	bool onButton();
	void slide();
	float calculateValue();
	bool getSlideButton();
private:
	Sprite* button,*bar;
	InputManager* input;
	float xBar,xButton,yBar,yButton,pastXButton;
	bool slideButton;
};

#endif /* SLIDER_H_ */
