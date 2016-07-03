/*
 * BlockWater.cpp
 *
 * Class responsible by handling the creation of water blocks.
 * 
 *  Created on: Nov 7, 2013
 *      Author: makoto
 */

#include "BlockWater.h"

BlockWater::BlockWater(Sprite * block, float x, float y):Block(block,x,y) {
	type = "BlockWater";
	animation = new Animation(20,20,block,0);
}

BlockWater::~BlockWater() {
	this->block = 0;
	delete this->block;
}

int BlockWater::update(int user_input_checker) {
	animation->update(user_input_checker,true,0,false);
	return 0;
}

void BlockWater::render(float camerax, float cameray) {
	animation->animate(150,this->x,this->y);
}

void BlockWater::reaction(Character * character) {
	this->tile->setBlock(0);
	this->tile = 0;
}
