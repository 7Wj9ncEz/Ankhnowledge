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
	this->currentSprite = sprite1;
	this->x = x;
	this->y = y;
	this->mouseX = 0;
	this->mouseY = 0;
	this->isPressed = false;
	this->changeScene = false;
	this->changeSprite = true;

}

Button::~Button() {
	this->sprite1->decNumRef();
	sprite1 = 0;
	this->sprite2->decNumRef();
	sprite2 = 0;

}


void Button::render(float camera_x, float camera_y){
	if(this->currentSprite) {
		this->currentSprite->render(this->x - camera_x,this->y - camera_y);
	}
}

int Button::update(int dt){

	if( (insideButton() == true) && (isPressed == false) && (changeSprite == true))
	{
		this->currentSprite = sprite2;
	}
	else if ((insideButton() == true) && (isPressed == true) && (changeSprite == true))
	{
		this->currentSprite = sprite3;
		this->changeScene = true;
	}
	else
	{
		this->currentSprite = sprite1;
	}

	return 0;
}

bool Button::insideButton(){
	return ((this->mouseX > this->x) && (this->mouseX < (this->x + this->currentSprite->getWidth())) &&
			(this->mouseY > this->y) && (this->mouseY < (this->y + this->currentSprite->getHeight())));
}

void Button::setMouseCoord(float coordinateX, float coordinateY) {
    //Passa as coordenadas x e y do lugar que foi clicado.
    this->mouseX = coordinateX;
    this->mouseY = coordinateY;

}

void Button::setChangeSprite(bool changeSprite){
	this->changeSprite = changeSprite;
}

void Button::mousePressed(bool isPressed){
	this->isPressed = isPressed;
}

bool Button::getChangeScene(){
	return this->changeScene;
}

