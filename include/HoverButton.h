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
	bool inside_button();
	virtual ~HoverButton();
	bool is_on_top();
	bool is_pressed();
	Sprite * get_sprite();
	float begin;

private:
	Sprite* sprite;
	bool on_top;
	bool pressed;
	InputManager *input;


};

#endif /* HOVERBUTTON_H_ */
