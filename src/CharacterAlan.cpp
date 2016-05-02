/*
 * CharacterAlan.cpp
 *
 * Class responsible by setting up all Alan's sprites and defining his skill.
 * 
 */


#include <iostream>

#include "CharacterAlan.h"
#include "SkillDig.h"
#include "Sprite.h"
#include "SDLBase.h"

#define DT 300

using namespace std;

CharacterAlan::CharacterAlan(Tile* tile, int id):Character(tile, id)
{
	this->sprite = new Sprite(SDLBase::resourcesPath + "adam_spr.png");
	sprite->incNumRef();
	this->hud = new Sprite(SDLBase::resourcesPath + "alanhud.png");
	hud->incNumRef();

	this->currentAnimation = new Animation(20,40,sprite,0);

	this->skill = new SkillDig();

	this->stamina = 10;
	this->initialStamina = 10;

}

CharacterAlan::~CharacterAlan()
{

}
