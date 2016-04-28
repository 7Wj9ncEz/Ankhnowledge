#include "SkillDig.h"
#include "Tile.h"
#include "Character.h"

SkillDig::SkillDig()
{
	this->requiredStamina = 6;
	this->considerBlocks = false;
	this->considerSand = false;
	this->reach = 3;
}

SkillDig::~SkillDig()
{
	
}

void SkillDig::execute(Tile * origin, Tile * dest)
{
	AudioHandler * audio = AudioHandler::getInstance();
 	audio->set_effect("dig_action.wav");
 	audio->play_effect(0);

	Character * character = origin->getCharacter();
	origin->setCharacter(0);
	character->setCurrentTile(dest);
	dest->setCharacter(character);
	character->setPosition(dest->getX(), dest->getY());
}

int SkillDig::getRequiredStamina()
{
	return this->requiredStamina;
}

bool SkillDig::getConsiderBlocks()
{
	return this->considerBlocks;
}


int SkillDig::getReach()
{
	return this->reach;
}
