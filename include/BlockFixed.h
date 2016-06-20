#ifndef BLOCKFIXED_H_
#define BLOCKFIXED_H_

#include "Character.h"
#include "Block.h"
#include "Animation.h"

class BlockFixed: public Block {
public:
	BlockFixed(Sprite * block, float x, float y);
	int update(int detective);
	void render(float camerax, float cameray);
	void reaction(Character * character);
	virtual ~BlockFixed();
	enum Direction {up, down, right, left, none};
	void interpolateMovement(float detective);


private:
	float end_x;
	float end_y;
	float begin_x;
	float begin_y;
	bool moving;
	Animation* animation;
};

#endif
