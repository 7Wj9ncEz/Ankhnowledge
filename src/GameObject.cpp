/*
 * GameObject.cpp
 *
 *  Class handles all the objects made in the game
 *
*/


#include "GameObject.h"
#include <assert.h>

/**
 * Regular constructor for GameObject that receives x and y (axis positions)
 *
 * Parameters:
 * "x & y" are the positions (in cm) used to verify the objects
**/
GameObject::GameObject(float x, float y) {

	// Asserts
	assert(x >= 0);
	assert(y >= 0);

	this->x = x;
	this->y = y;

}

GameObject::~GameObject() {

}

/**
 * Regular getter to receive the X position (in cm)
**/
float GameObject::getX() {
	return this->x;
}

/**
 * Regular getter to receive the Y position (in cm)
**/
float GameObject::getY() {
	return this->y;
}

/**
 * Responsible for interpolating and making the lerps in the Game
 *
 * Parameters:
 * "begin_x & begin_y" initial positions (in cm)
 * "end_x & end_y" final positions (in cm)
 * "time" responsible for handling the lerp
**/
bool GameObject::lerp(float begin_x, float begin_y, float end_x, float end_y, float time, float  dt) {

	// Asserts
	assert(begin_x >= 0);
	assert(begin_y >= 0);
	assert(end_x >= 0);
	assert(end_y >= 0);
	assert(time >= 0);
	assert(time < 10000);
	assert(dt >= 0);

	float x_percentage = 0;
	float y_percentage = 0;
	float total_x = end_x - begin_x;
	float total_y = end_y - begin_y;
	bool positive_x;
	bool positive_y;

	bool still_interpolating = false;

	if (begin_x > end_x) {
		positive_x = false;
		x_percentage = (begin_x - getX())/ total_x;
	}

	else {
		positive_x = true;
		x_percentage = (getX() - begin_x)/ total_x;
	}

	if (begin_y > end_y) {
		positive_y = false;
		y_percentage =  (begin_y - getY())/ total_y;
	}

	else {
		positive_y = true;
		y_percentage = (getY() - begin_y)/ total_y;
	}

	if (x_percentage < 1 && x_percentage > -1 && this->x != end_x) {
		still_interpolating = true;
		if (positive_x) {
			this->x = this->x + total_x*(total_x/time * dt/1000);
		}

		else {
			this->x = this->x - total_x*(total_x/time * dt/1000);
		}
	}

	else {
		this->x = end_x;
	}

	if (y_percentage < 1 && y_percentage > -1 && this->y != end_y) {
		still_interpolating = true;
		if (positive_y) {
			this->y = this->y + total_y*(total_y/time * dt/1000);
		}

		else {
			this->y = this->y - total_y*(total_y/time * dt/1000);
		}
	}

	else {
		this->y = end_y;
	}

	return still_interpolating;
}

/**
 * Sets the position of a game object
 *
 * Parameters:
 * "x & y" are the positions of the axis (in cm)
**/
void GameObject::setPosition(float x, float y) {

	// Asserts
	assert(x >= 0);
	assert(y >= 0);

	this->x = x;
	this->y = y;
}
