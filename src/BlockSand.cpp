/*
 * BlockMovable.cpp
 *
 * Class that handles how the Sand block interacts with characters.
 *
 */

#include "BlockSand.h"
#include <iostream>

using namespace std;

BlockSand::BlockSand(Sprite * block, float x, float y):Block(block,x,y) {
	type = "BlockSand";
	animation = new Animation(20,20,block,0);
}

BlockSand::~BlockSand() {
	this->block = 0;
	delete this->block;
}

int BlockSand::update(int detective) {
	animation->update(detective,true,0,false);
	return 0;
}

void BlockSand::render(float camerax, float cameray) {
	animation->animate(100,this->x,this->y);
}

void BlockSand::reaction(Character * character) {
	this->tile->setBlock(0);
	this->tile = 0;
}
