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
class Block: public GameObject 
{
public:
	virtual void render(float camera_x, float camera_y);
	virtual int update(int dt) = 0;
	string getType();
	virtual void reaction(Character * character) = 0;
	virtual ~Block();
	void setTile(Tile * tile);
	Tile * getTile();
	void setDestroyedAnimBlock(bool destroyed);
	void setDestroyedFinalBlock(bool destroyed);
	bool getDestroyedFinalBlock();

protected:
	Block(Sprite * block, float x, float y);
	Sprite* block;
	string type;
	Tile * tile;
	bool animDestroyed, finalDestroyed;
};

#endif /* BLOCK_H_ */
