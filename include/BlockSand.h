#ifndef BLOCKSAND_H_
#define BLOCKSAND_H_

#include "Character.h"
#include "Block.h"
#include "Animation.h"

class BlockSand: public Block {
	public:
		BlockSand(Sprite * block, float x, float y);
		int update(int user_input_checker);
		void render(float camerax, float cameray);
		virtual void reaction(Character * character);
		virtual ~BlockSand();

	private:
		Animation* animation;

};

#endif
