/*
 * Button.h
 *
 *  Created on: Oct 9, 2013
 *      Author: al
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "GameObject.h"
#include "Sprite.h"

class Button:public GameObject {
public:
	Button(Sprite* sprite1,Sprite* sprite2,Sprite* sprite3, float x,float y);
	void render(float camera_x,float camera_y);
	int update(int user_input_checker);
	void setMouseCoord(float coordinate_x, float coordinate_y);
	void mouse_pressed(bool is_pressed);
	bool inside_button();
	bool getChangeScene();
	virtual ~Button();
	void setChangeSprite(bool change_sprite);

private:
	Sprite* sprite1,*sprite2,*sprite3,*current_sprite;
	float x,y,mouse_x,mouse_y;
	bool is_pressed;
	bool change_scene;
	bool change_sprite;

};

#endif /* BUTTON_H_ */
