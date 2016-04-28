/*
 * HoverButton.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#include "HoverButton.h"

HoverButton::HoverButton(Sprite* sprite, float x, float y):GameObject(x,y) {
	this->sprite = sprite;
	this->sprite->incNumRef();
	onTop = false;
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
	if(insideButton())
		onTop = true;
	else
		onTop = false;

	if(insideButton() && this->input->isMouseDown(0))
	{
		pressed = true;
	}else
		pressed = false;

	return 0;
}

bool HoverButton::insideButton(){
	return ((this->input->mousePosX() > this->x) && (this->input->mousePosX() < (this->x + this->sprite->getWidth())) &&
			(this->input->mousePosY() > this->y) && (this->input->mousePosY() < (this->y + this->sprite->getHeight())));
}

bool HoverButton::isOnTop()
{
	return onTop;
}

bool HoverButton::isPressed()
{
	return pressed;
}

Sprite * HoverButton::getSprite()
{
	return this->sprite;
}



