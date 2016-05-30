/*
 * GameObject.cpp
 *
 *  Class handles all the objects made in the game
 *
 */


#include "GameObject.h"
#include <assert.h>

GameObject::GameObject(float x, float y) {

	// Asserts
	assert(x >= 0);
	assert(y >= 0);

	this->x = x;
	this->y = y;

}

GameObject::~GameObject() {

}

float GameObject::getX() {
	return this->x;
}

float GameObject::getY() {
	return this->y;
}

bool GameObject::lerp(float begin_x, float begin_y, float end_x, float end_y, float time, float  dt) {

	// Asserts
	assert(begin_x >= 0);
	assert(begin_y >= 0);
	assert(end_x >= 0);
	assert(end_y >= 0);
	assert(time >= 0);
	assert(time < 10000);
	assert(dt >= 0);

	float xPercentage = 0;
	float yPercentage = 0;
	float totalX = end_x - begin_x;
	float totalY = end_y - begin_y;
	bool positiveX;
	bool positiveY;

	bool stillInterpolating = false;

	if (begin_x > end_x) {
		positiveX = false;
		xPercentage = (begin_x - getX())/ totalX;
	}

	else {
		positiveX = true;
		xPercentage = (getX() - begin_x)/ totalX;
	}

	if (begin_y > end_y) {
		positiveY = false;
		yPercentage =  (begin_y - getY())/ totalY;
	}

	else {
		positiveY = true;
		yPercentage = (getY() - begin_y)/ totalY;
	}

	if (xPercentage < 1 && xPercentage > -1 && this->x != end_x) {
		stillInterpolating = true;
		if (positiveX) {
			this->x = this->x + totalX*(totalX/time * dt/1000);
		}

		else {
			this->x = this->x - totalX*(totalX/time * dt/1000);
		}
	}

	else {
		this->x = end_x;
	}

	if (yPercentage < 1 && yPercentage > -1 && this->y != end_y) {
		stillInterpolating = true;
		if (positiveY) {
			this->y = this->y + totalY*(totalY/time * dt/1000);
		}

		else {
			this->y = this->y - totalY*(totalY/time * dt/1000);
		}
	}

	else {
		this->y = end_y;
	}

	return stillInterpolating;
}

void GameObject::setPosition(float x, float y) {

	// Asserts
	assert(x >= 0);
	assert(y >= 0);

	this->x = x;
	this->y = y;
}
