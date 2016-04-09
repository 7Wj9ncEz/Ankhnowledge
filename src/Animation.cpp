/*
 * Animation.cpp
 *
 *  Created on: Oct 27, 2013
 *      Author: al
 */

#include "Animation.h"

Animation::Animation(int spriteWidth, int spriteHeight, Sprite* sprite, int direction) {
    //instancia um novo sprite
    this->animation = sprite;
    this->spriteWidth = spriteWidth;
    this->spriteHeight = spriteHeight;
    this->columns =  animation->getWidth() / spriteWidth;
    this->dt = 0;
    this->startFrame = direction * columns;
    this->prevDirection = direction;
    this->currentFrame = startFrame;
    this->animateSprite = true;
    this->finishedAnimation = false;

}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

void Animation::render(int index, float posX, float posY) {

	int x = index % columns;
	int y = index / columns;

	int clipx = x * spriteWidth;
	int clipy = y * spriteHeight;

	animation->clip(clipx, clipy, spriteWidth, spriteHeight);
	animation->render(posX, posY);
}

void Animation::animate(int frameRate,float posX, float posY) {
	this->frameRate = frameRate;
	render(currentFrame,posX,posY);
}

void Animation::update(int dt, bool onLoop, int direction, bool singleFrame) {
	this->dt = this->dt + dt;
	int lastFrame = columns;

	if (prevDirection != direction) {
		this->startFrame = direction * columns;
		this->currentFrame = startFrame;
		this->prevDirection = direction;
		this->finishedAnimation = false;
	}

  else {
    // Nothing to do
  }

	if(singleFrame) {
		lastFrame = 1;
		this->finishedAnimation = false;
	}

  else {
    // Nothing to do
  }

	if((this->dt > frameRate)) {
		if ((currentFrame == startFrame + lastFrame -1) && (onLoop == true)) {
			resetStartFrame();
			finishedAnimation = false;
		}

    else if ((currentFrame == startFrame + lastFrame -1) && (onLoop == false)) {
			this->finishedAnimation = true;
		}

		else {
			currentFrame++;
			this->dt = 0;
		}
	}

  else {
    // Nothing to do
  }

}

void Animation::resetStartFrame() {
	this->currentFrame = startFrame;
}

bool Animation::getFinishedAnimation() {
	return this->finishedAnimation;
}
