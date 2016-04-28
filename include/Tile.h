#ifndef TILE_H_
#define TILE_H_
#include "GameObject.h"
#include "Sprite.h"
#include "Character.h"
#include "Block.h"
#include "Animation.h"

class Block;
class Character;
class Tile: public GameObject {
public:
	Tile(Sprite * tile, Block * block, float x, float y, int id);
	void render(float camera_x, float camera_y);
	int update(int dt);
	virtual ~Tile();
	void setRightTile(Tile * tile);
	void setLeftTile(Tile * tile);
	void setUpTile(Tile * tile);
	void setDownTile(Tile * tile);
	Tile * getRightTile();
	Tile * getLeftTile();
	Tile * getUpTile();
	Tile * getDownTile();
	void cleanReferences();
	void setCharacter(Character * character);
	Character* getCharacter();
	Block* getBlock();
	bool insideTile();
	bool isClickable();
	void setClickable(bool click);
	void setBlock(Block * block);
	float getWidth();
	void animateClickableTiles(int dt);
	void renderClickableTiles();
	int id;
	static void setClickableTiles(Tile *origin, int reach, bool considerBlock,bool clickable);
	bool generateSandBlock();
	void createSandBlock();

private:
	Sprite* tile,*clickableTile;
	Block* block;
	Tile *leftTile, *rightTile, *upTile, *downTile;
	Character * character;
	Animation * animation;
	bool clickable;

};

#endif /* TILE_H_ */
