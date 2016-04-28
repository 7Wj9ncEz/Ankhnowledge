/*
 * HoverButton.h
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#ifndef HOVERBUTTON_H_
#define HOVERBUTTON_H_
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"

class HoverButton:public GameObject {
public:
	HoverButton(Sprite* sprite, float x,float y);
	void render(float camera_x,float camera_y);
	int update(int dt);
	bool insideButton();
	virtual ~HoverButton();
	bool isOnTop();
	bool isPressed();
	Sprite * getSprite();
	float begin;

private:
	Sprite* sprite;
	bool onTop;
	bool pressed;
	InputManager *input;


};

#endif /* HOVERBUTTON_H_ */
