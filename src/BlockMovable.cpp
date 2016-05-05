/*
 * BlockMovable.cpp
 *
 * Class responsible by setting how Movable blocks movements though the scenery.
 *
 *  Created on: Nov 5, 2013
 *      Author: makoto
 */

#include "BlockMovable.h"
#include <iostream>
using namespace std;
BlockMovable::BlockMovable(Sprite * block, float x, float y):Block(block,x,y) {
	type = "BlockMovable";
	moving = 0;
	animation = new Animation(20,20,block,0);
}

BlockMovable::~BlockMovable() {
 // Nothing to do
}

void BlockMovable::render(float camerax, float cameray) {
	animation->animate(150,this->x,this->y);
}

int BlockMovable::update(int dt) {
	interpolateMovement(dt);

	if (this->anim_destroyed)
	{
		animation->update(dt,false,0,false);
		if (animation->get_finished_animation()) {
			this->final_destroyed = true;
		}

		else {
			// Nothing to do
		}
	}

	else {
		animation->update(dt,true,0,true);
	}
	return 0;
}
void BlockMovable::reaction(Character * character) {
	Direction dir = none;
	character->incrementDiscountStamina(2);
	Tile * nextTile = 0;

	if (character->getCurrentTile()->getRightTile() == get_tile()) {
		dir = right;
		nextTile = get_tile()->getRightTile();
	}

	else if (character->getCurrentTile()->getLeftTile() == get_tile()) {
		dir = left;
		nextTile = get_tile()->getLeftTile();
	}

	else if (character->getCurrentTile()->getUpTile() == get_tile()) {
		dir = up;
		nextTile = get_tile()->getUpTile();
	}

	else if (character->getCurrentTile()->getDownTile() == get_tile()) {
		dir = down;
		nextTile = get_tile()->getDownTile();
	}

	if (nextTile && character->hasEnoughStamina() && !nextTile->getCharacter()) {
		if (!nextTile->getBlock()) {
			AudioHandler * audio = AudioHandler::getInstance();
		 	audio->set_effect("empurrar_bloco.wav");
		 	audio->play_effect(0);

			move(dir);
			get_tile()->setBlock(0);
			set_tile(nextTile);
			nextTile->setBlock(this);
		}

		else if (nextTile->getBlock()->getType() == "BlockMovable") {
			if (((BlockMovable *)(nextTile->getBlock()))->checkNextTile(character, this)) {
				AudioHandler * audio = AudioHandler::getInstance();
			 	audio->set_effect("empurrar_bloco.wav");
			 	audio->play_effect(0);

				move(dir);
				get_tile()->setBlock(0);
				set_tile(nextTile);
				nextTile->setBlock(this);
			}

			else {
				// Nothing to do
			}
		}

		else {
			character->resetDiscountStamina();
		}
	}

	else {
		character->resetDiscountStamina();
	}
}

bool BlockMovable::checkNextTile(Character * character, BlockMovable * lastBlock) {
	Direction dir = none;
	character->incrementDiscountStamina(1);
	Tile * nextTile = 0;

	if (lastBlock->get_tile()->getRightTile() == get_tile()) {
		dir = right;
		nextTile = get_tile()->getRightTile();
	}

	else if (lastBlock->get_tile()->getLeftTile() == get_tile()) {
		dir = left;
		nextTile = get_tile()->getLeftTile();
	}

	else if (lastBlock->get_tile()->getUpTile() == get_tile()) {
		dir = up;
		nextTile = get_tile()->getUpTile();
	}

	else if (lastBlock->get_tile()->getDownTile() == get_tile()) {
		dir = down;
		nextTile = get_tile()->getDownTile();
	}

	if (nextTile && character->hasEnoughStamina() && !nextTile->getCharacter()) {
		if (!nextTile->getBlock()) {
			move(dir);
			get_tile()->setBlock(0);
			set_tile(nextTile);
			nextTile->setBlock(this);
			return true;
		}

		else {
			// Nothing to do
		}

		else if (nextTile->getBlock()->getType() == "BlockMovable") {
			if (((BlockMovable *)(nextTile->getBlock()))->checkNextTile(character, this)) {
				move(dir);
				get_tile()->setBlock(0);
				set_tile(nextTile);
				nextTile->setBlock(this);
				return true;
			}

			else {
				// Nothing to do
			}
		}
	}

	else {
		// Nothing to do
	}

	character->resetDiscountStamina();
	return false;
}

void BlockMovable::move(Direction dir) {
	this->moving = true;
	switch (dir) {
	    case up:
	    	end_x = getX();
	    	end_y = getY() - 20;
	    break;

	    case down:
	    	end_x = getX();
			end_y = getY() + 20;
	    break;
	    case right:
	    	end_x = getX() + 20;
			end_y = getY();
	    break;

	    case left:
	    	end_x = getX() - 20;
			end_y = getY();

	    break;

	    case none:

	    break;
	}
	   begin_x = getX();
	   begin_y = getY();
}

void BlockMovable::interpolateMovement(float dt) {
	if (this->moving == true) {
		if (!lerp(begin_x, begin_y, end_x, end_y, 10, dt)) {
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
