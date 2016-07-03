/*
 * BlockFixed.cpp
 *
 * Class responsible by setting Fixed Blocks behaviour. 
 * 
 */

#include "BlockFixed.h"
#include <iostream>

using namespace std;

BlockFixed::BlockFixed(Sprite * block, float x, float y):Block(block,x,y)
{
	type = "BlockFixed";
	moving = 0;
	animation = new Animation(20,20,block,0);

}

BlockFixed::~BlockFixed() {}

void BlockFixed::render(float camerax, float cameray) {
	animation->animate(150,this->x,this->y);
}

int BlockFixed::update(int user_input_checker) {
	interpolateMovement(user_input_checker);

	if (this->anim_destroyed)	{
		animation->update(user_input_checker,false,0,false);
		if (animation->get_finished_animation()) {
			this->final_destroyed = true;
		}

		else {
			// Nothing to do
		}
	}

	else {
		animation->update(user_input_checker,true,0,true);
	}

	return 0;
}
void BlockFixed::reaction(Character * character) {
	// Nothing to do
}

void BlockFixed::interpolateMovement(float user_input_checker) {
	if (this->moving == true)
	{
		if (!lerp(begin_x, begin_y, end_x, end_y, 10, user_input_checker)) {
			this->moving = false;
		}

		else {
			// Nothing to do
		}
	}

	else {
		// Nothing to do
	}
}
