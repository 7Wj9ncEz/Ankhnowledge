#ifndef BLOCKWATER_H_
#define BLOCKWATER_H_

#include "Character.h"
#include "Block.h"
#include "Animation.h"

class BlockWater: public Block {
	public:
		BlockWater(Sprite * block, float x, float y);
		int update(int user_input_checker);
		void render(float camerax, float cameray);
		virtual void reaction(Character * character);
		virtual ~BlockWater();

	private:
		Animation* animation;

};

#endif /* BLOCK_H_ */
