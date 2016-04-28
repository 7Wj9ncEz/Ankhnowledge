/*
 * Map.h
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include "Sprite.h"
#include "InputManager.h"
#include <vector>
#include "GameObject.h"
#include "Character.h"
#include "Animation.h"
#include "Block.h"
#include <sstream>
#include <string>
#include "Button.h"
#include "TileMap.h"
#include "Network.h"
#include "FadeHandler.h"
#include "SDL/SDL.h"

using namespace std;

class Block;
class Character;
class Tile;
class TileMap;
class Map : public GameObject {
public:
	Map(Sprite * tile, Sprite * block, string mapLink, float x, float y);
	void render(float camera_x, float camera_y);
	int update(int dt);
	virtual ~Map();
	void mousePressed(Button *bt, InputManager* input);
	void mouseOver(Button *bt, InputManager * input);
	void changeCurrentPlayer();
	Tile * getTileWithIndex(int index);
	void tryToSpawnSand();
	void spawnSand(int id);

private:
	int columns;
	int rows;
	Sprite* tile;
	Sprite* block;
	Sprite* char1_spr;
	Sprite* char2_spr;
	Sprite* splashWon;
	FadeHandler * wonHandler;
	Sprite* splashLost;
	FadeHandler * lostHandler;
	Character * player1;
	Character * player2;
	Character * currentPlayer;
	vector<Tile* > tiles;
	TileMap *tileMap;
	bool changePlayer;

	bool isFirstRow(int index);
	bool isFirstColumn(int index);
	bool isLastRow(int index);
	bool isLastColumn(int index);
	Tile * getPressedTile();
	SDL_Color color;
	TTF_Font *font;
	TTF_Font *turn;
	Button* endButton;
	int deltaEnd;
	bool gameEnded;
};

#endif /* MAP_H_ */
