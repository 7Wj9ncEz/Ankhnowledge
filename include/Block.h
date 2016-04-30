/*
 * Block.h
 *
 *  Created on: Oct 28, 2013
 *      Author: makoto
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include "GameObject.h"
#include "Character.h"
#include "Tile.h"
#include <string>

class Tile;
class Character;
class Block: public GameObject {
public:
	virtual void render(float camera_x, float camera_y);
	virtual int update(int dt) = 0;
	string getType();
	virtual void reaction(Character * character) = 0;
	virtual ~Block();
	void set_tile(Tile * tile);
	Tile * get_tile();
	void set_destroyed_anim_block(bool destroyed);
	void set_destroyed_final_block(bool destroyed);
	bool get_destroyed_final_block();

protected:
	Block(Sprite * block, float x, float y);
	Sprite* block;
	string type;
	Tile * tile;
	bool anim_destroyed, final_destroyed;
};

#endif /* BLOCK_H_ */
