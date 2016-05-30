/*
 * HoverButton.cpp
 *
 * Class that shows if the mouse if hovering the button
 *
 */

#include "HoverButton.h"
#include <assert.h>

/**
 * With a sprite and it's positions it makes a button that will change when it's hovered
 *
 * Parameters:
 * "sprite" an object of Sprite that will be the button
 * "x & y" the positions (in pixels) that the hover "trigger" will be made
**/
HoverButton::HoverButton(Sprite* sprite, float x, float y):GameObject(x,y) {

	// Asserts
	assert(sprite != NULL);
	assert(x >= 0);
	assert(y >= 0);

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

/**
 * renders a HoverButton object on the positions given
 *
 * Parameters:
 * "camera_x & camera_y" the axis positions (in pixels) of where it will be rendered
**/
void HoverButton::render(float camera_x, float camera_y) {

	// Asserts
	assert(camera_x >= 0);
	assert(camera_y >= 0);

	if (this->sprite) {
		this->sprite->render(x,y);
	}

	else {
		// Nothing to do
	}
}

/**
 * Whenever there is a new update required this function updated the object HoverButton
**/
int HoverButton::update(int dt) {
	if (inside_button()) {
		on_top = true;
	}

	else {
		on_top = false;
	}

	if (inside_button() && this->input->is_mouse_down(0)) {
		pressed = true;
	}

	else {
		pressed = false;
	}

	return 0;
}

/**
 * Returns a boolean telling if the mouse is hovering the button or not
**/
bool HoverButton::inside_button() {
	return ((this->input->mouse_pos_x() > this->x) &&
			(this->input->mouse_pos_x() < (this->x + this->sprite->getWidth())) &&
			(this->input->mouse_pos_y() > this->y) &&
			(this->input->mouse_pos_y() < (this->y + this->sprite->getHeight())));
}

/**
 * A regular getter that returns the boolean value of "on_top"
**/
bool HoverButton::is_on_top() {
	return on_top;
}

/**
 * A regular getter that returns the boolean value of "pressed"
**/
bool HoverButton::is_pressed() {
	return pressed;
}

/**
 * A regular getter that returns an object "Sprite"
**/
Sprite * HoverButton::get_sprite() {
	return this->sprite;
}
