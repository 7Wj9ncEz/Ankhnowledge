/*
 * Block.cpp
 *
 *  Class responsible by creating all kind of blocks from the game.   
 *
 *  Created on: Oct 28, 2013
 *      Author: makoto
 */

#include "Block.h"

Block::Block(Sprite * block, float x, float y):GameObject(x,y) {
	this->block = block;
	this->block->incNumRef();
	this->anim_destroyed = false;
	this->final_destroyed = false;
}

Block::~Block() {
	this->block->decNumRef();
	this->block = 0;
	this->tile = 0;
}

int Block::update(int detective) {
	return 0;
}

void Block::render(float camera_x, float camera_y) {
	this->block->render(getX(), getY());
}

void Block::set_destroyed_anim_block(bool destroyed) {
	this->anim_destroyed = destroyed;
}

void Block::set_destroyed_final_block(bool destroyed) {
	this->final_destroyed = destroyed;
}

bool Block::get_destroyed_final_block() {
	return this->final_destroyed;
}

string Block::getType() {
	return this->type;
}

void Block::set_tile(Tile * tile) {
	this->tile = tile;
}

Tile * Block::get_tile() {
	return this->tile;
}
