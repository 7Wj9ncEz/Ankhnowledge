/*
 * GameObject.cpp
 *
 *  Class handles all the objects made in the game
 *
*/


#include "GameObject.h"
#include <assert.h>
#include "log.h"
#include "catch.hpp"

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

    // Init-Function Logs
    log("GameObject constructor called", GameObject);

    this->x = x;
    this->y = y;

	// Tests
    TEST_CASE("Testing GameObject Constructor", "[GameObject]") {
		REQUIRE(this->splashLogo != NULL);
		REQUIRE(this->splashTechnology != NULL);
    }

	// Mid-Function Logs
	log("lerp -> x = " + this->x, GameObject);
	log("lerp -> y = " + this->y, GameObject);

	// Post-Function Logs
	log("GameObject has ended", GameObject);

}

/**
 * Regular getter to receive the X position (in cm)
**/
float GameObject::getX() {

    // Init-Function Logs
    log("Get X called", GameObject);

    return this->x;

	// Post-Function Logs
	log("getX has ended", GameObject);
}

/**
 * Regular getter to receive the Y position (in cm)
**/
float GameObject::getY() {

    // Init-Function Logs
    log("Get Y called", GameObject);

    return this->y;

	// Post-Function Logs
	log("getY has ended", GameObject);
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

    // Init-Function Logs
    log("Lerp called", GameObject);

    float x_percentage = 0;
    float y_percentage = 0;
    float total_x = end_x - begin_x;
    float total_y = end_y - begin_y;
    bool positive_x = false;
    bool positive_y = false;
    bool still_interpolating = false;

	// Tests
    TEST_CASE("Testing lerp (GameObject)", "[GameObject]") {
		REQUIRE(x_percentage == 0);
		REQUIRE(y_percentage == 0);
		REQUIRE(total_x == end_x - begin_x);
		REQUIRE(total_y == end_y - begin_y);
		REQUIRE(positive_x == false);
		REQUIRE(positive_y == false);
		REQUIRE(still_interpolating == false);
    }

	// Mid-Function Logs
    log("lerp -> x_percentage = " + x_percentage, GameObject);
	log("lerp -> y_percentage = " + y_percentage, GameObject);
	log("lerp -> total_x = " + total_x, GameObject);
	log("lerp -> total_y = " + total_y, GameObject);
	log("lerp -> positive_x = " + positive_x, GameObject);
	log("lerp -> positive_y = " + positive_y, GameObject);
	log("lerp -> still_interpolating = " + still_interpolating, GameObject);

    if (begin_x > end_x) {
        positive_x = false;
        x_percentage = (begin_x - getX())/ total_x;

		// Mid-Function Logs
	    log("lerp -> positive_x = " + positive_x, GameObject);
		log("lerp -> x_percentage = " + x_percentage, GameObject);
    }

    else {
        positive_x = true;
        x_percentage = (getX() - begin_x)/ total_x;

		// Mid-Function Logs
	    log("lerp -> positive_x = " + positive_x, GameObject);
		log("lerp -> x_percentage = " + x_percentage, GameObject);
    }

    if (begin_y > end_y) {
        positive_y = false;
        y_percentage =  (begin_y - getY())/ total_y;

		// Mid-Function Logs
	    log("lerp -> positive_y = " + positive_y, GameObject);
		log("lerp -> y_percentage = " + y_percentage, GameObject);
    }

    else {
        positive_y = true;
        y_percentage = (getY() - begin_y)/ total_y;

		// Mid-Function Logs
	    log("lerp -> positive_y = " + positive_y, GameObject);
		log("lerp -> y_percentage = " + y_percentage, GameObject);
    }

    if (x_percentage < 1 && x_percentage > -1 && this->x != end_x) {
        still_interpolating = true;
        if (positive_x) {
            this->x = this->x + total_x*(total_x/time * dt/1000);

			// Mid-Function Logs
		    log("lerp -> x = " + this->x, GameObject);
        }

        else {
            this->x = this->x - total_x*(total_x/time * dt/1000);

			// Mid-Function Logs
		    log("lerp -> x = " + this->x, GameObject);        }
    }

    else {
        this->x = end_x;

		// Mid-Function Logs
		log("lerp -> x = " + this->x, GameObject);
    }

    if (y_percentage < 1 && y_percentage > -1 && this->y != end_y) {
        still_interpolating = true;
        if (positive_y) {
            this->y = this->y + total_y*(total_y/time * dt/1000);

			// Mid-Function Logs
		    log("lerp -> y = " + this->y, GameObject);
        }

        else {
            this->y = this->y - total_y*(total_y/time * dt/1000);

			// Mid-Function Logs
		    log("lerp -> y = " + this->y, GameObject);
        }
    }

    else {
        this->y = end_y;

		// Mid-Function Logs
		log("lerp -> y = " + this->y, GameObject);
    }

    return still_interpolating;

	// Post-Function Logs
	log("lerp has ended", GameObject);
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

	// Init-Function Logs
    log("Set Position called", GameObject);

    this->x = x;
    this->y = y;

	// Mid-Function Logs
	log("lerp -> x = " + this->x, GameObject);
	log("lerp -> y = " + this->y, GameObject);

	// Post-Function Logs
	log("setPosition has ended", GameObject);
}
