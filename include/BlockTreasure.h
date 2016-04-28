/*
 * BlockTreasure.h
 *
 *  Created on: Nov 7, 2013
 *      Author: makoto
 */

#ifndef BLOCKTREASURE_H_
#define BLOCKTREASURE_H_
#include "Character.h"
#include "Block.h"
#include "Animation.h"

class BlockTreasure: public Block
{
public:
	BlockTreasure(Sprite * block, float x, float y);
	int update(int dt);
	virtual void reaction(Character * character);
	virtual ~BlockTreasure();
	void render(float camera_x, float cameray);

private:
	bool open;
	bool activated;
	Animation* animation;

};

#endif /* BLOCKTREASURE_H_ */
