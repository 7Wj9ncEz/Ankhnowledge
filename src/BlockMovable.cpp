/*
 * BlockMovable.cpp
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

}

void BlockMovable::render(float camerax, float cameray){
	animation->animate(150,this->x,this->y);
}

int BlockMovable::update(int dt)
{
	interpolateMovement(dt);

	if(this->animDestroyed)
	{
		animation->update(dt,false,0,false);
		if(animation->getFinishedAnimation())
		{
			this->finalDestroyed = true;
		}
	}
	else
	{
		animation->update(dt,true,0,true);
	}
	return 0;
}
void BlockMovable::reaction(Character * character)
{
	Direction dir = none;
	character->incrementDiscountStamina(2);
	Tile * nextTile = 0;

	if(character->getCurrentTile()->getRightTile() == getTile())
	{
		dir = right;
		nextTile = getTile()->getRightTile();
	}
	else if(character->getCurrentTile()->getLeftTile() == getTile())
	{
		dir = left;
		nextTile = getTile()->getLeftTile();
	}
	else if(character->getCurrentTile()->getUpTile() == getTile())
	{
		dir = up;
		nextTile = getTile()->getUpTile();
	}
	else if(character->getCurrentTile()->getDownTile() == getTile())
	{
		dir = down;
		nextTile = getTile()->getDownTile();
	}

	if(nextTile && character->hasEnoughStamina() && !nextTile->getCharacter())
	{
		if(!nextTile->getBlock())
		{
			AudioHandler * audio = AudioHandler::getInstance();
		 	audio->setEffect("empurrar_bloco.wav");
		 	audio->playEffect(0);

			move(dir);
			getTile()->setBlock(0);
			setTile(nextTile);
			nextTile->setBlock(this);
		}
		else if(nextTile->getBlock()->getType() == "BlockMovable")
		{
			if(((BlockMovable *)(nextTile->getBlock()))->checkNextTile(character, this))
			{
				AudioHandler * audio = AudioHandler::getInstance();
			 	audio->setEffect("empurrar_bloco.wav");
			 	audio->playEffect(0);

				move(dir);
				getTile()->setBlock(0);
				setTile(nextTile);
				nextTile->setBlock(this);
			}
		}
		else
		{
			character->resetDiscountStamina();
		}

	}
	else
	{
		character->resetDiscountStamina();
	}
}

bool BlockMovable::checkNextTile(Character * character, BlockMovable * lastBlock)
{
	Direction dir = none;
	character->incrementDiscountStamina(1);
	Tile * nextTile = 0;

	if(lastBlock->getTile()->getRightTile() == getTile())
	{
		dir = right;
		nextTile = getTile()->getRightTile();
	}else if(lastBlock->getTile()->getLeftTile() == getTile())
	{
		dir = left;
		nextTile = getTile()->getLeftTile();
	}else if(lastBlock->getTile()->getUpTile() == getTile())
	{
		dir = up;
		nextTile = getTile()->getUpTile();
	}else if(lastBlock->getTile()->getDownTile() == getTile())
	{
		dir = down;
		nextTile = getTile()->getDownTile();
	}

	if(nextTile && character->hasEnoughStamina() && !nextTile->getCharacter())
	{
		if(!nextTile->getBlock())
		{
			move(dir);
			getTile()->setBlock(0);
			setTile(nextTile);
			nextTile->setBlock(this);
			return true;

		}else if(nextTile->getBlock()->getType() == "BlockMovable")
		{
			if(((BlockMovable *)(nextTile->getBlock()))->checkNextTile(character, this))
			{
				move(dir);
				getTile()->setBlock(0);
				setTile(nextTile);
				nextTile->setBlock(this);
				return true;
			}
		}
	}

	character->resetDiscountStamina();
	return false;
}

void BlockMovable::move(Direction dir)
{
	this->moving = true;
	switch(dir)
	{
	    case up:
	    	endX = getX();
	    	endY = getY() - 20;
	    break;

	    case down:
	    	endX = getX();
			endY = getY() + 20;
	    break;
	    case right:
	    	endX = getX() + 20;
			endY = getY();
	    break;

	    case left:
	    	endX = getX() - 20;
			endY = getY();

	    break;

	    case none:

	    break;
	}
	   beginX = getX();
	   beginY = getY();
}

void BlockMovable::interpolateMovement(float dt)
{
	if(this->moving == true)
	{
		if(!lerp(beginX, beginY, endX, endY, 10, dt))
		{
			this->moving = false;
		}
		else
		{
			// do nothing
		}
	}
	else
	{
		// do nothing
	}
}
