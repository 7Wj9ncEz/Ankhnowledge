/*
 * Button.cpp
 *
 * Class responsible by creating and rendering all game interface buttons.
 */

#include "Button.h"
#include <assert.h>
#include "log.h"
#include "catch.hpp"

/**
 * Responsible for creating a Button object
 *
 * Parameters:
 * "sprite1 & sprite2 & sprite3" sprite Objects that will be used to form the Button
 * "x & y" positions in the axis (in pixels)
**/
Button::Button(Sprite* sprite1,Sprite* sprite2,Sprite* sprite3, float x, float y):GameObject(getX(),getY()) {

	// Asserts
	assert(sprite1 != NULL);
	assert(sprite2 != NULL);
	assert(sprite3 != NULL);

	// Init-Function Logs
    log("Button constructor called", Button);

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

	// Tests
    TEST_CASE("Testing Button Constructor", "[Button]") {
		REQUIRE(this->sprite1 == 0);
		REQUIRE(this->sprite2 == 0);
		REQUIRE(this->sprite3 == sprite3);
		REQUIRE(this->current_sprite == sprite1);
		REQUIRE(this->x == x);
		REQUIRE(this->y == y);
		REQUIRE(this->mouse_x == 0);
		REQUIRE(this->mouse_y == 0);
		REQUIRE(this->is_pressed == false);
		REQUIRE(this->change_scene == false);
		REQUIRE(this->change_sprite == false);
    }

	// Mid-Function Logs
	log("Button -> sprite1 = " + this->sprite1, Button);
	log("Button -> sprite2 = " + this->sprite2, Button);
	log("Button -> sprite3 = " + this->sprite3, Button);
	log("Button -> current_sprite = " + this->current_sprite, Button);
	log("Button -> x = " + this->x, Button);
	log("Button -> y = " + this->y, Button);
	log("Button -> mouse_x = " + this->mouse_x, Button);
	log("Button -> mouse_y = " + this->mouse_y, Button);
	log("Button -> is_pressed = " + this->is_pressed, Button);
	log("Button -> change_scene = " + this->change_scene, Button);
	log("Button -> change_scene = " + this->change_scene, Button);

	// Post-Function Logs
	log("Button has ended", Button);
}

/**
 * Responsible for removing data from the Button object
 **/
Button::~Button() {

	// Init-Function Logs
    log("Button destructor called", Button);

	this->sprite1->decNumRef();
	sprite1 = 0;
	this->sprite2->decNumRef();
	sprite2 = 0;

	// Tests
    TEST_CASE("Testing Button Destructor", "[Button]") {
		REQUIRE(this->sprite1 == 0);
		REQUIRE(this->sprite2 == 0);
	}

	// Mid-Function Logs
	log("Button -> sprite1 = " + this->sprite1, Button);
	log("Button -> sprite2 = " + this->sprite2, Button);

	// Post-Function Logs
	log("Button destructor has ended", Button);
}

/**
 * Responsible for rendering a Button
 *
 * Parameters:
 * "camera_x & camera_y" positions on x and y axis to render the Button (in pixels)
**/
void Button::render(float camera_x, float camera_y) {

	// Init-Function Logs
    log("Render has been called", Button);

	if (this->current_sprite) {
		this->current_sprite->render(this->x - camera_x,this->y - camera_y);

		// Mid-Function Logs
		log("render -> current_sprite has called render()", Button);
	}

	// Post-Function Logs
	log("render has ended", Button);
}

/**
 * Responsible for updating the GameManager
**/
int Button::update(int detective) {

	// Init-Function Logs
    log("Update has been called", Button);

	if ((inside_button() == true) && (is_pressed == false) && (change_sprite == true)) {
		this->current_sprite = sprite2;

		// Mid-Function Logs
		log("update -> current_sprite = " + this->current_sprite, Button);
	}

	else if ((inside_button() == true) && (is_pressed == true) && (change_sprite == true)) {
		this->current_sprite = sprite3;
		this->change_scene = 0;

		// Mid-Function Logs
		log("update -> current_sprite = " + this->current_sprite, Button);
		log("update -> change_scene = " + this->change_scene, Button);
	}

	else {
		this->current_sprite = sprite1;

		// Mid-Function Logs
		log("update -> current_sprite = " + this->current_sprite, Button);
	}

	return 0;

	// Post-Function Logs
	log("update has ended", Button);
}

/**
 * Returns a boolean value that shows if the mouse is hovering (inside) the Button
**/
bool Button::inside_button() {
	return ((this->mouse_x > this->x) && (this->mouse_x < (this->x + this->current_sprite->getWidth())) &&
			(this->mouse_y > this->y) && (this->mouse_y < (this->y + this->current_sprite->getHeight())));
}

void Button::setMouseCoord(float coordinate_x, float coordinate_y) {

	// Init-Function Logs
    log("Set Mouse Coord has been called", Button);

	//Passa as coordenadas x e y do lugar que foi clicado.
    this->mouse_x = coordinate_x;
    this->mouse_y = coordinate_y;

	// Mid-Function Logs
	log("setMouseCoord -> mouse_x = " + this->mouse_x, Button);
	log("setMouseCoord -> mouse_y = " + this->mouse_y, Button);

	// Tests
    TEST_CASE("Testing setMouseCoord (Button)", "[Button]") {
		REQUIRE(this->mouse_x == coordinate_x);
		REQUIRE(this->mouse_y == coordinate_y);
	}

	// Post-Function Logs
	log("setMouseCoord has ended", Button);
}

/**
 * Regular setter for change_sprite
 *
 * Parameters:
 * "change_sprite" a boolean value that shows if the button has to change sprite
**/
void Button::setChangeSprite(bool change_sprite) {

	// Init-Function Logs
    log("Set Change Sprite has been called", Button);

	this->change_sprite = change_sprite;

	// Post-Function Logs
	log("setChangeSprite -> change_sprite = " + this->change_sprite, Button);
	log("setChangeSprite has ended", Button);
}

/**
 * Regular setter for mouse_pressed
 *
 * Parameters:
 * "is_pressed" a boolean value that shows if the button has been pressed or not
**/
void Button::mouse_pressed(bool is_pressed) {

	// Init-Function Logs
    log("Mouse Pressed has been called", Button);

	this->is_pressed = is_pressed;

	// Post-Function Logs
	log("mouse_pressed -> is_pressed = " + this->is_pressed, Button);
	log("mouse_pressed has ended", Button);
}

/**
 * Returns the change_scene object
**/
bool Button::getChangeScene() {

	// Init-Function Logs
    log("Get Change Scene has been called", Button);

	return this->change_scene;

	// Post-Function Logs
	log("getChangeScene has ended", Button);
}
