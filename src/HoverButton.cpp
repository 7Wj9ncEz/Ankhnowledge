/*
 * HoverButton.cpp
 *
 * Class responsible by setting what a button does when hovered. 
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#include "HoverButton.h"

HoverButton::HoverButton(Sprite* sprite, float x, float y):GameObject(x,y) {
	this->sprite = sprite;
	this->sprite->incNumRef();
	on_top = false;
	pressed = false;
	input = InputManager::getInstance();
}

HoverButton::~HoverButton() {
	this->sprite->decNumRef();
	sprite = 0;

}


void HoverButton::render(float camera_x, float camera_y){
	if(this->sprite) {
		this->sprite->render(x,y);
	}
}

int HoverButton::update(int dt){
	if(inside_button())
		on_top = true;
	else
		on_top = false;

	if(inside_button() && this->input->is_mouse_down(0))
	{
		pressed = true;
	}else
		pressed = false;

	return 0;
}

bool HoverButton::inside_button(){
	return ((this->input->mouse_pos_x() > this->x) && (this->input->mouse_pos_x() < (this->x + this->sprite->getWidth())) &&
			(this->input->mouse_pos_y() > this->y) && (this->input->mouse_pos_y() < (this->y + this->sprite->getHeight())));
}

bool HoverButton::is_on_top()
{
	return on_top;
}

bool HoverButton::is_pressed()
{
	return pressed;
}

Sprite * HoverButton::get_sprite()
{
	return this->sprite;
}



