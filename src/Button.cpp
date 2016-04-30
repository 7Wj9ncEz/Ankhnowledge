/*
 * Button.cpp
 *
 *  Created on: Oct 9, 2013
 *      Author: al
 */

#include "Button.h"

Button::Button(Sprite* sprite1,Sprite* sprite2,Sprite* sprite3, float x, float y):GameObject(getX(),getY()) {
	this->sprite1 = sprite1;
	this->sprite1->incNumRef();
	this->sprite2 = sprite2;
	this->sprite2->incNumRef();
	this->sprite3 = sprite3;
	this->sprite3->incNumRef();
	this->current_sprite = sprite1;
	this->x = x;
	this->y = y;
	this->mouse_x = 0;
	this->mouse_y = 0;
	this->is_pressed = false;
	this->change_scene = false;
	this->change_sprite = true;

}

Button::~Button() {
	this->sprite1->decNumRef();
	sprite1 = 0;
	this->sprite2->decNumRef();
	sprite2 = 0;

}


void Button::render(float camera_x, float camera_y){
	if(this->current_sprite) {
		this->current_sprite->render(this->x - camera_x,this->y - camera_y);
	}
}

int Button::update(int dt){

	if( (insideButton() == true) && (is_pressed == false) && (change_sprite == true))
	{
		this->current_sprite = sprite2;
	}
	else if ((insideButton() == true) && (is_pressed == true) && (change_sprite == true))
	{
		this->current_sprite = sprite3;
		this->change_scene = true;
	}
	else
	{
		this->current_sprite = sprite1;
	}

	return 0;
}

bool Button::insideButton(){
	return ((this->mouse_x > this->x) && (this->mouse_x < (this->x + this->current_sprite->getWidth())) &&
			(this->mouse_y > this->y) && (this->mouse_y < (this->y + this->current_sprite->getHeight())));
}

void Button::setMouseCoord(float coordinate_x, float coordinate_y) {
    //Passa as coordenadas x e y do lugar que foi clicado.
    this->mouse_x = coordinate_x;
    this->mouse_y = coordinate_y;

}

void Button::setChangeSprite(bool change_sprite){
	this->change_sprite = change_sprite;
}

void Button::mousePressed(bool is_pressed){
	this->is_pressed = is_pressed;
}

bool Button::getChangeScene(){
	return this->change_scene;
}

