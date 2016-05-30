/*
 * FadeHandler.cpp
 *
 *  Class made to handle the fade in the game
 *
 */

#include "FadeHandler.h"
#include <iostream>
#include <assert.h>
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

	this->sprite = sprite;
	this->should_fade_in = false;
	this->should_fade_out = false;
	this->current_percentage = ((float)sprite->getAlpha()/255);

}

/**
 * Regular constructor without sprite
**/
FadeHandler::~FadeHandler() {
	this->sprite = 0;
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

	this->should_fade_in = true;
	this->should_fade_out = false;
	this->percentage_of_stop = percentage;
	this->current_percentage = ((float)sprite->getAlpha()/255);
	this->rate = (this->percentage_of_stop - this->current_percentage)/time;
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

	this->should_fade_out = true;
	this->should_fade_in = false;
	this->percentage_of_stop = percentage;
	this->current_percentage = ((float)sprite->getAlpha()/255);
	this->rate = (this->current_percentage - this->percentage_of_stop)/time;

}

/**
 * Responsible for updating the fade in the game
**/
void FadeHandler::update(float dt) {

	// Asserts
	assert(dt >= 0);

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
		}

		else {
			should_fade_in = false;
			current_percentage = percentage_of_stop;
			sprite->setAlpha(255*current_percentage);
		}
	}

	else if (should_fade_out) {
		if (current_percentage > percentage_of_stop) {
			current_percentage -= rate*dt/1000;
			sprite->setAlpha(255*current_percentage);
		}

		else {
			should_fade_out = false;
			current_percentage = percentage_of_stop;
			sprite->setAlpha(255*current_percentage);
		}
	}

	else {
		// Nothing to do
	}

}

/**
 * Regular getter that returns a float value for the "current_percentage"
 * The percentage is related to the fade
**/
float FadeHandler::get_current_percentage() {
	return this->current_percentage;
}
