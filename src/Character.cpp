/*
 * Character.cpp
 *
 * Class responsible by setting up Character's behaviour, and how he interacts with Button pressing.
 * 
 *  Created on: Nov 7, 2013
 *      Author: makoto
 */


#include <iostream>
#include "Character.h"
#include "Skill.h"
#include <sstream>
#include <stdlib.h>

#define DT 300

using namespace std;

Character::Character(Tile* tile, int id):GameObject(tile->getX(),tile->getY())
{
	this->currentTile = tile;
	tile->setCharacter(this);
	this->x = tile->getX();
	this->y = tile->getY();
	this->activatedSkill = false;
	this->performingAction = false;
	this->turn = false;
	this->id = id;
	this->direction = 4;
	this->skillDestTile = 0;
	this->user_input_checker = 0;
	discountStamina = 0;
	this->win = false;
	this->on_loop = true;
	this->map = 0;
}

Character::~Character()
{
	/*this->currentTile = 0;
	this->sprite->decNumRef();
	this->hud->decNumRef();
	this->skill = 0;
	this->skillDestTile = 0;
	sprite = 0;
	this->hud = 0;
	this->map = 0;*/
}

void Character::render(float camera_x, float camera_y)
{
	currentAnimation->animate(100, this->x - camera_x,this->y - camera_y - 40/2);
}

int Character::update(int user_input_checker)
{
	InputManager* input;
	input = InputManager::getInstance();
	
	this->user_input_checker = this->user_input_checker + user_input_checker;

	if (this->activatedSkill)
	{
		if (this->user_input_checker > DT)
		{
			if (input->is_key_pressed(SDLK_y) && Network::get_id() == this->id)
			{
				deactivateSkill();
				send_message("DeactivateSkill", "-1");

			}
			else if (this->skillDestTile && Network::get_id() == this->id)
			{	
				useSkill(skillDestTile->id);
				send_message("UseSkill", intToString(skillDestTile->id));
				skillDestTile = 0;
			}
			
			this->user_input_checker = 0;
		}
	}
	
	else
	{
		if (turn && !performingAction && Network::get_id() == this->id)
		{
			if (input->is_key_pressed(SDLK_y))
			{
				if (this->user_input_checker > DT)
				{
					if((this->skill) && (this->stamina >= this->skill->getRequiredStamina()))
					{
						activateSkill();
						send_message("ActivateSkill", "-1");
					}

					this->user_input_checker = 0;
				}
			}
		}
		
		if (turn && !performingAction && input->is_key_pressed(SDLK_u) && Network::get_id() == this->id)
		{
			pushUpdate(input);
		}
		else if (turn && !performingAction && Network::get_id() == this->id)
		{
			moveUpdate(input);
		}
	}

	if (turn && !performingAction && Network::get_id() != this->id)
		receive_message();

	interpolateMovement(user_input_checker);
	if (activatedSkill == true)
	{
		on_loop = false;
		direction = 5;
	}
	if((activatedSkill == false) && currentAnimation->get_finished_animation())
	{
		on_loop = false;
		if (direction == 5)
			direction = 6;
		else if (direction == 6)
			direction = 4;
	}
	else if ((direction != 5) && (direction != 6))
	{
		on_loop = true;
	}



	currentAnimation->update(user_input_checker, on_loop, direction,false);
	return 0;
}

void Character::push(Direction dir)
{
	this->performingAction = true;
	switch(dir)
	{
		case up:
			end_x = getX();
			end_y = getY() - currentTile->getWidth();
			direction = 3;
		break;

		case down:
			end_x = getX();
			end_y = getY() + currentTile->getWidth();
			direction = 0;
		break;
		case right:
			end_x = getX() + currentTile->getWidth();
			end_y = getY();
			direction = 2;
		break;

		case left:
			end_x = getX() - currentTile->getWidth();
			end_y = getY();
			direction = 1;

		break;

		case none:

		break;

	}

	   begin_x = getX();
	   begin_y = getY();
}

void Character::move(Direction dir)
{
	this->performingAction = true;
	this->stamina -= 1;
	switch(dir)
	{
	    case up:
	    	end_x = getX();
	    	end_y = getY() - currentTile->getWidth();
	    	direction = 3;
	    break;

	    case down:
	    	end_x = getX();
			end_y = getY() + currentTile->getWidth();
			direction = 0;
	    break;
	    case right:
	    	end_x = getX() + currentTile->getWidth();
	    	end_y = getY();
	    	direction = 2;
	    break;

	    case left:
	    	end_x = getX() - currentTile->getWidth();
			end_y = getY();
			direction = 1;
	    break;

	    case none:

	    break;

	}

	   begin_x = getX();
	   begin_y = getY();
}

void Character::interpolateMovement(float user_input_checker)
{
	if (this->performingAction == true)
	{
		if(!lerp(begin_x, begin_y, end_x, end_y, 10, user_input_checker))
		{
			this->performingAction = false;
			direction = 4;
		}
	}

}

int Character::getStamina()
{
	return this->stamina;
}

int Character::getInitialStamina()
{
	return this->initialStamina;
}

void Character::setStamina(int stamina)
{
	this->stamina = stamina;
	if (this->stamina < 0)
		this->stamina = 0;
}

void Character::setSkill(Skill * skill)
{
	this->skill = skill;
}

void Character::setTurn(bool on)
{
	turn = on;
}

void Character::toogleTurn()
{
	if (turn == true)
		turn = false;
	else
		turn = true;
}

int Character::getId()
{
	return this->id;
}

bool Character::isPerformingAction()
{
	return this->performingAction;
}

bool Character::isUsingSkill()
{
	return this->activatedSkill;
}

void Character::setCurrentTile(Tile * tile)
{
	this->currentTile = tile;
}

Tile * Character::getCurrentTile()
{
	return this->currentTile;
}

void Character::changeCurrentTile(Tile * tile)
{
	currentTile->setCharacter(0);
	currentTile = tile;
	currentTile->setCharacter(this);
}

bool Character::canChangeTile(Tile * tile)
{
	if (tile == 0)
		return false;

	if (tile->getCharacter() != 0)
		return false;

	if (tile->getBlock())
	{
		if (tile->getBlock()->getType() == "BlockMovable")
		return false;
	}


	return true;
}

void Character::setSkillDestTile(Tile * tile)
{
	this->skillDestTile = tile;
}

void Character::incrementDiscountStamina(int value)
{
	this->discountStamina += value;
}

void Character::resetDiscountStamina()
{
	this->discountStamina = 0;
}

bool Character::hasEnoughStamina()
{
	return	(discountStamina <= stamina);
}

void Character::pushUpdate(InputManager * input, Direction dir)
{

	bool needToSend = true;
		if (dir != none)
			needToSend = false;

	Tile * nextTile = 0;
	if (input->is_key_pressed(SDLK_d) || dir == right)
	{
		dir = right;
		nextTile = currentTile->getRightTile();
	}else
	if (input->is_key_pressed(SDLK_a) || dir == left)
	{
		dir = left;
		nextTile = currentTile->getLeftTile();
	}else
	if (input->is_key_pressed(SDLK_s) || dir == down)
	{
		dir = down;
		nextTile = currentTile->getDownTile();
	}else
	if (input->is_key_pressed(SDLK_w) || dir == up)
	{
		dir = up;
		nextTile = currentTile->getUpTile();
	}

	Block * block = 0;
	if (nextTile)
	{
		block = nextTile->getBlock();
	}
	discountStamina = 0;
	if (block)
	{
		if (block->getType() == "BlockMovable")
		{
			block->reaction(this);
		}
	}

	if (discountStamina != 0 && hasEnoughStamina())
	{
		stamina -= discountStamina;

		if (stamina < 0)
			stamina = 0;

		discountStamina = 0;
		push(dir);
		if (needToSend)
			send_message("Push", intToString((int)dir));
		changeCurrentTile(nextTile);
	}


	block = 0;
	nextTile = 0;
}

void Character::moveUpdate(InputManager * input, Direction dir)
{
	bool needToSend = true;
	if (dir != none)
		needToSend = false;

	Tile * nextTile = 0;
	if ((input->is_key_pressed(SDLK_d) && canChangeTile(currentTile->getRightTile()) && dir == none) || dir == right)
	{
		dir = right;
		nextTile = currentTile->getRightTile();
	}else
	if ((input->is_key_pressed(SDLK_a) && canChangeTile(currentTile->getLeftTile()) && dir == none) || dir == left)
	{
		dir = left;
		nextTile = currentTile->getLeftTile();
	}else
	if ((input->is_key_pressed(SDLK_s)  && canChangeTile(currentTile->getDownTile()) && dir == none) || dir == down)
	{
		dir = down;
		nextTile = currentTile->getDownTile();
	}else
	if ((input->is_key_pressed(SDLK_w)  && canChangeTile(currentTile->getUpTile()) && dir == none) || dir == up)
	{
		dir = up;
		nextTile = currentTile->getUpTile();
	}


	if (nextTile)
	{
		Block * block = 0;
		block = nextTile->getBlock();

		if (block)
		{
			if (block->getType() == "BlockTreasure")
			{
				block->reaction(this);
				if (needToSend)
					send_message("Move", intToString((int)dir));
			}
			if (block->getType() == "BlockSand")
			{
				changeCurrentTile(nextTile);
				if (dir != none && !performingAction)
				{
					move(dir);
					if (needToSend)
						send_message("Move", intToString((int)dir));
				}
				nextTile->setBlock(0);
				setStamina(getStamina() - 3);
				AudioHandler * audio = AudioHandler::getInstance();
			 	audio->set_effect("areia_movedica.wav");
			 	audio->play_effect(0);

				//delete block;
			}
			if (block->getType() == "BlockWater")
			{
				changeCurrentTile(nextTile);
				if (dir != none && !performingAction)
				{
					move(dir);
					if (needToSend)
						send_message("Move", intToString((int)dir));
				}
				nextTile->setBlock(0);
				setStamina(getStamina() + 2);
				this->initialStamina += 2;
				AudioHandler * audio = AudioHandler::getInstance();
			 	audio->set_effect("pote.wav");
			 	audio->play_effect(0);

				//delete block;
			}
		}else
		{
			changeCurrentTile(nextTile);
			if (dir != none && !performingAction)
			{
				move(dir);
				if (needToSend)
					send_message("Move", intToString((int)dir));
			}
		}

		block = 0;
	}

	nextTile = 0;
}

bool Character::getWin()
{
	return this->win;
}

void Character::setWin(bool win)
{
	this->win = win;
}

bool Character::getTurn()
{
	return this->turn;
}

Sprite * Character::getHud()
{
	return this->hud;
}

void Character::send_message(string action, string info)
{

	string direction;
	string msg = action + " " + info;
	Network::send_message(msg);

}

string Character::intToString(int intenger)
{
	string st;
	ostringstream convert;
	convert << intenger;
	st = convert.str();
	return st;
}

void Character::activateSkill()
{
	activatedSkill = true;
	Tile::setClickableTiles(currentTile, skill->getReach(), skill->getConsiderBlocks(), true);
}

void Character::deactivateSkill()
{
	activatedSkill = false;
	Tile::setClickableTiles(currentTile, skill->getReach(), skill->getConsiderBlocks(), false);
}

void Character::useSkill(int tileIndex)
{
	this->stamina -= skill->getRequiredStamina();
	Tile::setClickableTiles(currentTile, skill->getReach(), skill->getConsiderBlocks(), false);
	skill->execute(this->currentTile, map->get_tile_with_index(tileIndex));
	this->activatedSkill = false;
}

void Character::setMap(Map * map)
{
	this->map = map;
}

void Character::spawnSand(string msg)
{
	send_message("SpawnSand", msg);
}

void Character::receive_message()
{
	string message = Network::read_message();
	if (message == "")
		return;

	istringstream iss(message);

	string action;
	string info;

	iss >> action;
	iss >> info;


	if (action == "Move")
	{
		moveUpdate(InputManager::getInstance(), (Direction)atoi(info.c_str()));
	}
	else
	if (action == "Push")
	{
		pushUpdate(InputManager::getInstance(), (Direction)atoi(info.c_str()));
	}
	else
	if (action == "ActivateSkill")
	{
		activateSkill();
	}
	if (action == "DeactivateSkill")
	{
		deactivateSkill();
	}
	if (action == "UseSkill")
	{
		useSkill((Direction)atoi(info.c_str()));
	}
	if (action == "EndTurn")
	{
		map->change_current_player();
	}
	if (action == "SpawnSand")
	{
		map->spawnSand(atoi(info.c_str()));
		while(true)
		{
			string info2;
			iss >> info2;

			if (info2 != "end")
			{
				map->spawnSand(atoi(info2.c_str()));
			}
			else
			{
				break;
			}
		}
	}
}


