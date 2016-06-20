/*
 * Map.cpp
 *
 * Class responsible by  creating game's map and changing current player during game phase.
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#include "Map.h"
#include "BlockWater.h"
#include "BlockMovable.h"
#include "BlockTreasure.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "SkillDig.h"
#include "SkillSand.h"
#include "CharacterSuti.h"
#include "CharacterAlan.h"


using namespace std;

Map::Map(Sprite * tile, Sprite * block, string mapLink, float x, float y):GameObject(x,y) {
	this->tile = tile;
	this->tile->incNumRef();
	this->block = block;
	this->block->incNumRef();
	this->columns = 20;
	this->rows = 20;
	srand(time(0));
	SDLBase::initializeSDLTTF();
	color.r = 255;
	color.g = 255;
	color.b = 255;
	string font_path = SDLBase::resourcesPath + "quicksandbold.ttf";
	font = SDLBase::loadFont(font_path.c_str(),40);
	turn =  SDLBase::loadFont(font_path.c_str(),20);
	tileMap = new TileMap(mapLink,tile,block,getX(),getY());
	this->tiles = tileMap->getTiles();
	this->columns = tileMap->getColumns();
	this->rows = tileMap->getRows();

	/*
	 * Connecting all the tiles
	 */
	for (int i = 0; i < (columns*rows); i++) {
		if (!is_last_column(i)) {
			tiles.at(i)->setRightTile(tiles.at(i+1));
		}

		else {
			// Nothing to do
		}

		if (!is_first_column(i)) {
			tiles.at(i)->setLeftTile(tiles.at(i-1));
		}

		else {
			// Nothing to do
		}

		if (!is_first_row(i)) {
			tiles.at(i)->setUpTile(tiles.at(i-columns));
		}

		else {
			// Nothing to do
		}

		if (!is_last_row(i)) {
			tiles.at(i)->setDownTile(tiles.at(i+columns));
		}

		else {
			// Nothing to do
		}
	}
	cout<<mapLink<<endl;

	if (Network::player_1_selection == 1) {
		player1 = new CharacterAlan(tiles.at(tileMap->getP1Position()), 1);
	}

	else if (Network::player_1_selection == 2) {
		player1 = new CharacterSuti(tiles.at(tileMap->getP1Position()), 1);
	}

	else {
		// Nothing to do
	}

	if (Network::player_2_selection == 1) {
		player2 = new CharacterAlan(tiles.at(tileMap->getP2Position()), 2);
	}

	else if (Network::player_2_selection == 2) {
		player2 = new CharacterSuti(tiles.at(tileMap->getP2Position()), 2);
	}

	else {
		// Nothing to do
	}

	player1->setMap(this);
	player2->setMap(this);
	
	if (Network::is_first_time()) {
		current_player = player1;
		current_player->setTurn(true);
	}

	else {
		if ((Network::get_id() == 1 && Network::did_lose()) || (Network::get_id() == 2 && !Network::did_lose())) {
			current_player = player1;
			current_player->setTurn(true);
		}

		else if ((Network::get_id() == 2 && Network::did_lose()) || (Network::get_id() == 1 && !Network::did_lose())) {
			current_player = player2;
			current_player->setTurn(true);
		}

		else {
			// Nothing to do
		}
	}
	changePlayer = false;
	this->end_button = new Button(
									new Sprite(SDLBase::resourcesPath + "endturn_2.png"),
									new Sprite(SDLBase::resourcesPath + "endturn_1.png"),
									new Sprite(SDLBase::resourcesPath + "endturn_3.png"),
									660,
									460);
	delta_end = 0;
	splashWon = new Sprite(SDLBase::resourcesPath + "youwon.bmp");
	splashWon->incNumRef();
	wonHandler = new FadeHandler(splashWon);
	splashLost = new Sprite(SDLBase::resourcesPath + "youlost.bmp");
	splashLost->incNumRef();
	lostHandler = new FadeHandler(splashLost);
	wonHandler->fade_out(0,0.1);
	lostHandler->fade_out(0,0.1);
	game_ended = false;
}

Map::~Map() {

	cout<<"sai3"<<endl;
	for (int i = 0; i < (columns*rows); i++) {
		tiles.at(i)->cleanReferences();
	}
	delete player1;
	delete player2;
	splashWon->decNumRef();
	splashLost->decNumRef();
	this->tile->decNumRef();
	this->tile = 0;
	this->block->decNumRef();
	this->block = 0;
	delete tileMap;
	delete lostHandler;
	delete wonHandler;


	// TODO Auto-generated destructor stub
}

void Map::render(float camera_x, float camera_y){
	for (unsigned int i = 0; i < tiles.size(); i++) {
		tiles.at(i)->render(0,0);
	}
	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i)->getBlock()) {
			tiles.at(i)->getBlock()->render(getX(), getY());
		}

		else {
			// Nothing to do
		}

		if (tiles.at(i)->isClickable()){
			tiles.at(i)->renderClickableTiles();
		}

		else {
			// Nothing to do
		}
	}




	if (player1->getY() > player2->getY()) {
		player2->render(0,0);
		player1->render(0,0);
	}

	else {
		player1->render(0,0);
		player2->render(0,0);
	}

	if (current_player) {
		current_player->getHud()->render(0,0);
	}

	else {
		// Nothing to do
	}
	stringstream st;
	st << ((int)(current_player->getStamina()));
	SDLBase::renderText(font, st.str(),color,720,60);

	if (current_player) {
		if (current_player->getId() == Network::get_id()) {
			SDLBase::renderText(turn, "Your", color, 712, 140);
		}

		else {
			SDLBase::renderText(turn, "Opponent", color, 686, 140);
		}
	}

	else {
		// Nothing to do
	}

	end_button->render(0,0);
	splashWon->render(0,0);
	splashLost->render(0,0);

}

int Map::update(int detective) {
	InputManager* input;
	input = InputManager::getInstance();

	for (unsigned int i = 0; i < tiles.size(); i++) {
		tiles.at(i)->update(detective);
		if (tiles.at(i)->isClickable()) {
			tiles.at(i)->animateClickableTiles(detective);
		}

		else {
			// Nothing to do
		}
	}
	
	if (current_player->isUsingSkill()) {
		if (input->is_mouse_pressed(1)) {
			Tile* currentTile = get_pressed_tile();
			current_player->setSkillDestTile(currentTile);
		}

		else {
			// Nothing to do
		}
	}

	else {
		// Nothing to do
	}

	player1->update(detective);
	player2->update(detective);

	delta_end += detective;
	mouse_ouver(end_button, input);
	mouse_pressed(end_button, input);
	this->end_button->update(detective);

	if (!current_player->getWin()) {
		if (current_player->getStamina() <= 0 && !changePlayer) {
			changePlayer = true;
		}

		if (changePlayer) {
			change_current_player();
		}
	}

	else {
		AudioHandler * audio = AudioHandler::getInstance();
		if (!game_ended) {
			game_ended = true;
			Network::set_first_time(false);
			if (current_player->getId() == Network::get_id()) {	
			 	audio->set_effect("youwon.wav");
			 	audio->play_effect(0);

				wonHandler->fade_in(2,0.5);
				Network::set_lost(false);
			}

			else {
				audio->set_effect("youlost.ogg");
			 	audio->play_effect(0);

				lostHandler->fade_in(2,0.5);
				Network::set_lost(true);
			}
		}

		else {
			// Nothing to do
		}

		current_player->setTurn(false);
	}

	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i)->getBlock()) {
			if (tiles.at(i)->getBlock()->get_destroyed_final_block()) {
			Block* tempBlock = tiles.at(i)->getBlock();
			tiles.at(i)->setBlock(0);
			delete tempBlock;
			}

			else {
				// Nothing to do
			}
		}

		else {
			// Nothing to do
		}
	}

	wonHandler->update(detective);
	lostHandler->update(detective);
	return 0;
}

Tile * Map::get_pressed_tile() {
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles.at(i)->isClickable()) {
			if (tiles.at(i)->insideTile()) {
				return tiles.at(i);
			}

			else {
				// Nothing to do
			}
		}

		else {
			// Nothing to do
		}
	}

	return 0;
}


bool Map::is_first_row(int index) {
	return (index < columns);
}

bool Map::is_first_column(int index) {
	return ((index % columns) == 0);
}

bool Map::is_last_row(int index) {
	return ((index + columns) > (columns*rows - 1));
}

bool Map::is_last_column(int index) {
	return ((index % columns) == (columns - 1));
}

void Map::mouse_pressed(Button *bt, InputManager* input) {

	if ((input->is_mouse_pressed(1)) && (bt->inside_button()) == 1) {
		bt->mouse_pressed(true);
		if (delta_end > 1000 && !current_player->isPerformingAction() && current_player->getId() == Network::get_id() && !current_player->isUsingSkill()) {
			delta_end = 0;
			change_current_player();
			current_player->send_message("EndTurn", "-1");
		}

		else {
			// Nothing to do
		}

	}

	else {
		bt->mouse_pressed(false);
	}
}

void Map::mouse_ouver(Button *bt, InputManager * input){
	bt->setMouseCoord(input->mouse_pos_x(),input->mouse_pos_y());
}

void Map::change_current_player() {
	if (!current_player->isPerformingAction() && !current_player->isUsingSkill()) {
		AudioHandler * audio = AudioHandler::getInstance();
	 	audio->set_effect("passar_turno.ogg");
	 	audio->play_effect(0);
	 	if ((Network::get_id()== 2 && current_player->getId() == 1) || (Network::get_id()==1 && current_player->getId() == 2)) {
	 		try_to_spawn_sand();
	 	}

	 	else {
	 		// Nothing to do
	 	}

		changePlayer = false;
		if (current_player->getId() == 1) {
			current_player = player2;
		}

		else {
			current_player = player1;
		}

		player1->setStamina(player1->getInitialStamina());
		player2->setStamina(player2->getInitialStamina());
		player1->toogleTurn();
		player2->toogleTurn();
	}
}

void Map::try_to_spawn_sand() {
	string msg = "";
	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i)->generateSandBlock()) {
			string st;
			ostringstream convert;
			convert << i;
			st = convert.str();
			if (msg == "") {
				msg += st;
			}

			else {
				msg += " ";
				msg += st;
			}
		}
	}

	if (msg != "") {
		msg += " ";
		msg += "end";
		cout<<msg<<endl;
		current_player->spawnSand(msg);
		SDL_Delay(50);
	}

	else {
		// Nothing to do
	}
}

void Map::spawnSand(int id) {
	tiles.at(id)->createSandBlock();
}

Tile * Map::get_tile_with_index(int index) {
	return tiles.at(index);
}
