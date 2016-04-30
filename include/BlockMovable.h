/*
 * BlockMovable.h
 *
 *  Created on: Nov 5, 2013
 *      Author: makoto
 */

#ifndef BLOCKMOVABLE_H_
#define BLOCKMOVABLE_H_

#include "Character.h"
#include "Block.h"
#include "Animation.h"

class BlockMovable: public Block
{
public:
	BlockMovable(Sprite * block, float x, float y);
	int update(int dt);
	void render(float camerax, float cameray);
	void reaction(Character * character);
	virtual ~BlockMovable();
	bool checkNextTile(Character * character, BlockMovable * lastBlock);
	enum Direction { up, down, right, left, none };
	void move(Direction dir);
	void interpolateMovement(float dt);


private:
	float end_x;
	float end_y;
	float begin_x;
	float begin_y;
	bool moving;
	Animation* animation;
};

#endif /* BLOCKMOVABLE_H_ */
