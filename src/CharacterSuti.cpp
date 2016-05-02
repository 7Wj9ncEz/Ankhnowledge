/*
 * CharacterAlan.cpp
 *
 * Class responsible by setting up all Suti's sprites and defining his skill.
 * 
 */


#include <iostream>

#include "CharacterSuti.h"
#include "SkillSand.h"
#include "Sprite.h"
#include "SDLBase.h"

#define DT 300

using namespace std;

CharacterSuti::CharacterSuti(Tile* tile, int id):Character(tile, id)
{
	this->sprite = new Sprite(SDLBase::resourcesPath + "suti_spr.png");
	sprite->incNumRef();
	this->hud = new Sprite(SDLBase::resourcesPath + "sutihud.png");
	hud->incNumRef();

	this->currentAnimation = new Animation(20,40,sprite,0);
	
	this->skill = new SkillSand();

	this->stamina = 12;
	this->initialStamina = 12;
}

CharacterSuti::~CharacterSuti()
{

}
