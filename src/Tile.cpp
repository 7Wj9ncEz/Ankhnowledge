#include "Tile.h"
#include "SDLBase.h"
#include <sstream>
#include "BlockSand.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

Tile::Tile(Sprite * tile, Block * block,float x, float y, int id):GameObject(x,y) {
	this->tile = tile;
	this->tile->incNumRef();
	this->block = block;
	this->leftTile = 0;
	this->rightTile = 0;
	this->upTile = 0;
	this->downTile = 0;
	this->id = id;
	this->character = 0;
	this->clickable = false;
	this->clickableTile = new Sprite(SDLBase::resourcesPath + "whitesquare.png");
	this->clickableTile->incNumRef();
	this->animation = new Animation(20,20,clickableTile,0);

	if (block) {
		block->setTile(this);
	}

	else {
		// Nothing to do
	}
}

Tile::~Tile() {
	this->tile->decNumRef();
	this->tile = 0;
	this->clickableTile->decNumRef();
	this->clickableTile = 0;
	delete block;

	// TODO Auto-generated destructor stub
}

void Tile::render(float cameraX, float cameraY){

	if (tile) {
		tile->render(getX(), getY());
	}

	else {
		// Nothing to do
	}
}


int Tile::update(int dt) {

	if (block) {
		block->update(dt);
	}

	else {
		// Nothing to do
	}

	return 0;
}

void Tile::renderClickableTiles() {
	animation->animate(50,getX(),getY());
}

void Tile::animateClickableTiles(int dt) {
	animation->update(dt,true,0,0);
}

bool Tile::insideTile() {
	InputManager* input;
	input = InputManager::getInstance();

	return ((input->mousePosX() > this->x) && (input->mousePosX() < (this->x + this->tile->getWidth())) &&
			(input->mousePosY() > this->y) && (input->mousePosY() < (this->y + this->tile->getHeight())));

}

void Tile::setLeftTile(Tile * tile) {
	this->leftTile = tile;
}

void Tile::setRightTile(Tile * tile) {
	this->rightTile = tile;
}

void Tile::setUpTile(Tile * tile) {
	this->upTile = tile;
}

void Tile::setDownTile(Tile * tile) {
	this->downTile = tile;
}

Tile * Tile::getRightTile() {
	return this->rightTile;
}

Tile * Tile::getLeftTile() {
	return this->leftTile;
}

Tile * Tile::getUpTile() {
	return this->upTile;
}

Tile * Tile::getDownTile() {
	return this->downTile;
}

void Tile::cleanReferences() {
	this->leftTile  = 0;
	this->rightTile = 0;
	this->upTile = 0;
	this->downTile = 0;
}

void Tile::setCharacter(Character * character) {
	this->character = character;
}

Character * Tile::getCharacter() {
	return this->character;
}

Block * Tile::getBlock() {
	return this->block;
}

bool Tile::isClickable() {
	return this->clickable;
}

void Tile::setClickable(bool click) {
	if (click) {
		animation->resetStartFrame();
	}

	else {
		// Nothing to do
	}

	this->clickable = click;
}

void Tile::setBlock(Block * block) {
	this->block = block;
}

float Tile::getWidth() {
	return tile->getWidth();
}

void Tile::setClickableTiles(Tile *origin, int reach, bool considerBlock, bool clickable) {
	int i = 1;
	Tile *tile = origin;

	if (i <= reach && tile->getUpTile()) {
		tile = tile->getUpTile();

		if (!tile->getCharacter()) {

			if (!tile->getBlock()) {
				tile->setClickable(clickable);
			}

			else if (considerBlock) {
				if (tile->getBlock()->getType() == "BlockSand" || tile->getBlock()->getType() == "BlockWater") {
					// Nothing to do
				}

				else {
					tile->setClickable(clickable);
				}
			}

			else {
				// Nothing to do
			}
		}

		else {
			// Nothing to do
		}

		Tile::setClickableTiles(tile, reach-1, considerBlock, clickable);
	}

	else {
		// Nothing to do
	}

	tile = origin;

	if (i <= reach && tile->getDownTile()) {
		tile = tile->getDownTile();

		if (!tile->getCharacter()) {

			if (!tile->getBlock()) {
				tile->setClickable(clickable);
			}

			else if (considerBlock)	{
				if (tile->getBlock()->getType() == "BlockSand" || tile->getBlock()->getType() == "BlockWater") {
					// Nothing to do
				}
				else {
					tile->setClickable(clickable);
				}
			}

			else {
				// Nothing to do
			}
		}

		else {
			// Nothing to do
		}

		Tile::setClickableTiles(tile, reach-1, considerBlock, clickable);
	}

	else {
		// Nothing to do
	}

	tile = origin;

	if (i <= reach && tile->getLeftTile()) {
		tile = tile->getLeftTile();

		if (!tile->getCharacter()) {
			if (!tile->getBlock())	{
				tile->setClickable(clickable);
			}

			else if (considerBlock)	{
				if(tile->getBlock()->getType() == "BlockSand" || tile->getBlock()->getType() == "BlockWater")	{
					//Do nothing
				}

				else {
					tile->setClickable(clickable);
				}
			}

			else {
				// Nothing to do
			}
		}

		else {
			// Nothing to do
		}

		Tile::setClickableTiles(tile, reach-1, considerBlock, clickable);
	}

	else {
		// Nothing to do
	}

	tile = origin;

	if (i <= reach && tile->getRightTile())	{
		tile = tile->getRightTile();

		if (!tile->getCharacter())	{
			if (!tile->getBlock())	{
				tile->setClickable(clickable);
			}

			else if (considerBlock)	{
				if (tile->getBlock()->getType() == "BlockSand" || tile->getBlock()->getType() == "BlockWater") {
					//Do nothing
				}

				else {
					tile->setClickable(clickable);
				}
			}

			else {
				// Nothing to do
			}
		}

		else {
			// Nothing to do
		}

		Tile::setClickableTiles(tile, reach-1, considerBlock, clickable);
	}

	else {
		// Nothing to do
	}
}

bool Tile::generateSandBlock()
{
	if (block || character) {
		return false;
	}

	else {
		// Nothing to do
	}

	int random = rand()%101;
	if (random < 2) {
		this->createSandBlock();
		return true;
	}

	else {
		// Nothing to do
	}

	return false;
}

void Tile::createSandBlock()
{
	Block *newBlock = new BlockSand(new Sprite(SDLBase::resourcesPath + "areiamovedica.png"), this->getX(), this->getY());
	this->setBlock(newBlock);
}
