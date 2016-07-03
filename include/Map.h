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
	int update(int user_input_checker);
	virtual ~Map();
	void mouse_pressed(Button *bt, InputManager* input);
	void mouse_ouver(Button *bt, InputManager * input);
	void change_current_player();
	Tile * get_tile_with_index(int index);
	void try_to_spawn_sand();
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
	Character * current_player;
	vector<Tile* > tiles;
	TileMap *tileMap;
	bool changePlayer;

	bool is_first_row(int index);
	bool is_first_column(int index);
	bool is_last_row(int index);
	bool is_last_column(int index);
	Tile * get_pressed_tile();
	SDL_Color color;
	TTF_Font *font;
	TTF_Font *turn;
	Button* end_button;
	int delta_end;
	bool game_ended;
};

#endif /* MAP_H_ */
