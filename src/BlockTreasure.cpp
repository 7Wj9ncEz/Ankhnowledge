/*
 * BlockTreasure.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: makoto
 */

#include "BlockTreasure.h"
#include <iostream>
using namespace std;

BlockTreasure::BlockTreasure(Sprite * block, float x, float y):Block(block,x,y) {
	type = "BlockTreasure";
	this->open = false;
	this->activated = false;
	animation = new Animation(20,20,block,0);
}

BlockTreasure::~BlockTreasure() {
 // Nothing to do
}

void BlockTreasure::render(float cameraX,float cameraY) {
	animation->animate(50,this->x,this->y);
}

int BlockTreasure::update(int dt)
{
	if(open)
	{
		animation->update(dt,false,0,false);
		if (GameManager::currentScene->changeScene("SceneSelectCharacter") == 1 && !activated && animation->getFinishedAnimation() == true) {
			activated = true;
			GameManager::fadeScreen->fadeIn(1,2);
		}
		/*Adicionar pra animar o bau abrindo e parar no ultimo frame
		 * Quando a animacao acabar mudar pra tela de ganhou
		 */
	}

	else {
		animation->update(dt,false,0,true);
	}

	return 0;
}

void BlockTreasure::reaction(Character * character) {
	character->setWin(true);
	open = true;
}
