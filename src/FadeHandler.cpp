/*
 * FadeHandler.cpp
 *
 *  Class made to handle the fade in the game
 *
 */

#include "FadeHandler.h"
#include <iostream>
#include <assert.h>
#include "log.h"
#include "catch.hpp"
using namespace std;

/**
 * Creates a FadeHandler to handle the fade of a specific sprite
 *
 * Parameters:
 * "sprite" references to a Sprite object that will have it's fade handled
**/
FadeHandler::FadeHandler(Sprite * sprite) {

	// Asserts
	assert(sprite != NULL);

	// Init-Function Logs
    log("FadeHandler constructor called", FadeHandler);

	this->sprite = sprite;
	this->should_fade_in = false;
	this->should_fade_out = false;
	this->current_percentage = ((float)sprite->getAlpha()/255);

	// Tests
    TEST_CASE("Testing FadeHandler Constructor", "[GameObject]") {
		REQUIRE(this->sprite == sprite);
		REQUIRE(this->should_fade_in == false);
		REQUIRE(this->should_fade_out == false);
		REQUIRE(this->current_percentage == ((float)sprite->getAlpha()/255));
    }

	// Mid-Function Logs
	log("FadeHandler -> sprite = " + this->sprite, FadeHandler);
	log("FadeHandler -> should_fade_in = " + this->should_fade_in, FadeHandler);
	log("FadeHandler -> should_fade_out = " + this->should_fade_out, FadeHandler);
	log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);

	// Post-Function Logs
	log("FadeHandler has ended", FadeHandler);
}

/**
 * Regular constructor without sprite
**/
FadeHandler::~FadeHandler() {

	// Init-Function Logs
    log("FadeHandler destructor called", FadeHandler);

	this->sprite = 0;

	// Tests
    TEST_CASE("Testing FadeHandler Destructor", "[GameObject]") {
		REQUIRE(this->sprite == 0);
    }

	// Mid-Function Logs
	log("lerp -> sprite = " + this->sprite, FadeHandler);

	// Post-Function Logs
	log("FadeHandler destructor has ended", FadeHandler);
}

/**
 * Responsible for providing the fade
 *
 * Parameters:
 * "percentage" represents the amount of fade to be done (from 0 to 100)
 * "time" represents the time to fade in (in seconds)
**/
void FadeHandler::fade_in(float percentage, float time) {

	// Asserts
	assert(percentage >= 0);
	assert(percentage <= 100);
	assert(time >= 0);
	assert(time < 10000);

	// Init-Function Logs
    log("Fade Handler constructor called", FadeHandler);

	this->should_fade_in = true;
	this->should_fade_out = false;
	this->percentage_of_stop = percentage;
	this->current_percentage = ((float)sprite->getAlpha()/255);
	this->rate = (this->percentage_of_stop - this->current_percentage)/time;

	// Tests
    TEST_CASE("Testing fade_in (FadeHandler)", "[GameObject]") {
		REQUIRE(this->should_fade_in == true);
		REQUIRE(this->should_fade_out == false);
		REQUIRE(this->percentage_of_stop == percentage);
		REQUIRE(this->current_percentage == ((float)sprite->getAlpha()/255));
		REQUIRE(this->rate == (this->percentage_of_stop - this->current_percentage)/time);
    }

	// Mid-Function Logs
	log("FadeHandler -> should_fade_in = " + this->should_fade_in, FadeHandler);
	log("FadeHandler -> should_fade_out = " + this->should_fade_out, FadeHandler);
	log("FadeHandler -> percentage_of_stop = " + this->percentage_of_stop, FadeHandler);
	log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);
	log("FadeHandler -> rate = " + this->rate, FadeHandler);

	// Post-Function Logs
	log("fade_in has ended", FadeHandler);
}

/**
 * Responsible for removing the fade
 *
 * Parameters:
 * "percentage" represents the amount of fade still left (from 100 to 0)
 * "time" represents the time to fade out (in seconds)
**/
void FadeHandler::fade_out(float percentage, float time) {

	// Asserts
	assert(percentage >= 0);
	assert(percentage <= 100);
	assert(time >= 0);
	assert(time < 10000);

	// Init-Function Logs
    log("Fade Handler called", FadeHandler);

	this->should_fade_out = true;
	this->should_fade_in = false;
	this->percentage_of_stop = percentage;
	this->current_percentage = ((float)sprite->getAlpha()/255);
	this->rate = (this->current_percentage - this->percentage_of_stop)/time;

	// Tests
    TEST_CASE("Testing fade_out (FadeHandler)", "[GameObject]") {
		REQUIRE(this->should_fade_in == false);
		REQUIRE(this->should_fade_out == true);
		REQUIRE(this->percentage_of_stop == percentage);
		REQUIRE(this->current_percentage == ((float)sprite->getAlpha()/255));
		REQUIRE(this->rate == (this->current_percentage - this->percentage_of_stop)/time);
    }

	// Mid-Function Logs
	log("FadeHandler -> should_fade_in = " + this->should_fade_in, FadeHandler);
	log("FadeHandler -> should_fade_out = " + this->should_fade_out, FadeHandler);
	log("FadeHandler -> percentage_of_stop = " + this->percentage_of_stop, FadeHandler);
	log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);
	log("FadeHandler -> rate = " + this->rate, FadeHandler);

	// Post-Function Logs
	log("fade_out has ended", FadeHandler);
}

/**
 * Responsible for updating the fade in the game
**/
void FadeHandler::update(float dt) {

	// Asserts
	assert(dt >= 0);

	// Init-Function Logs
    log("Update called", FadeHandler);

	if (!this->sprite) {
		return;
	}

	else {
		// Nothing to do
	}
	/*cout << "current_percentage: " << this->current_percentage << endl;
	cout << "should_fade_in: " << this->should_fade_in << endl;
	cout << "should_fade_out: " << this->should_fade_out << endl;
	cout << "rate: " << this->rate << endl;
	cout << "dt : " << dt << endl;*/
	if (should_fade_in) {
		if (current_percentage < percentage_of_stop) {
			current_percentage += rate * dt/1000;
			sprite->setAlpha(255*current_percentage);

			// Mid-Function Logs
			log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);
			log("FadeHandler -> sprite = " + this->sprite, FadeHandler);
		}

		else {
			should_fade_in = false;
			current_percentage = percentage_of_stop;
			sprite->setAlpha(255*current_percentage);

			// Mid-Function Logs
			log("FadeHandler -> should_fade_in = " + this->should_fade_in, FadeHandler);
			log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);
			log("FadeHandler -> sprite = " + this->sprite, FadeHandler);
		}
	}

	else if (should_fade_out) {
		if (current_percentage > percentage_of_stop) {
			current_percentage -= rate*dt/1000;
			sprite->setAlpha(255*current_percentage);

			// Mid-Function Logs
			log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);
			log("FadeHandler -> sprite = " + this->sprite, FadeHandler);
		}

		else {
			should_fade_out = false;
			current_percentage = percentage_of_stop;
			sprite->setAlpha(255*current_percentage);

			// Mid-Function Logs
			log("FadeHandler -> should_fade_out = " + this->should_fade_out, FadeHandler);
			log("FadeHandler -> current_percentage = " + this->current_percentage, FadeHandler);
			log("FadeHandler -> sprite = " + this->sprite, FadeHandler);
		}
	}

	else {
		// Nothing to do
	}

	// Post-Function Logs
	log("update has ended", FadeHandler);
}

/**
 * Regular getter that returns a float value for the "current_percentage"
 * The percentage is related to the fade
**/
float FadeHandler::get_current_percentage() {

	// Init-Function Logs
    log("Get Current Percentage called", FadeHandler);

	return this->current_percentage;

	// Post-Function Logs
	log("get_current_percentage has ended", FadeHandler);
}
