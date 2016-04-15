/*
 * Map.cpp
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
		if (!isLastColumn(i)) {
			tiles.at(i)->setRightTile(tiles.at(i+1));
		}

		else {
			// Nothing to do
		}

		if (!isFirstColumn(i)) {
			tiles.at(i)->setLeftTile(tiles.at(i-1));
		}

		else {
			// Nothing to do
		}

		if (!isFirstRow(i)) {
			tiles.at(i)->setUpTile(tiles.at(i-columns));
		}

		else {
			// Nothing to do
		}

		if (!isLastRow(i)) {
			tiles.at(i)->setDownTile(tiles.at(i+columns));
		}

		else {
			// Nothing to do
		}
	}
	cout<<mapLink<<endl;

	if (Network::player1Selection == 1) {
		player1 = new CharacterAlan(tiles.at(tileMap->getP1Position()), 1);
	}

	else if (Network::player1Selection == 2) {
		player1 = new CharacterSuti(tiles.at(tileMap->getP1Position()), 1);
	}

	else {
		// Nothing to do
	}

	if (Network::player2Selection == 1) {
		player2 = new CharacterAlan(tiles.at(tileMap->getP2Position()), 2);
	}

	else if (Network::player2Selection == 2) {
		player2 = new CharacterSuti(tiles.at(tileMap->getP2Position()), 2);
	}

	else {
		// Nothing to do
	}

	player1->setMap(this);
	player2->setMap(this);
	
	if (Network::isFirstTime()) {
		currentPlayer = player1;
		currentPlayer->setTurn(true);
	}

	else {
		if ((Network::getID() == 1 && Network::didLost()) || (Network::getID() == 2 && !Network::didLost())) {
			currentPlayer = player1;
			currentPlayer->setTurn(true);
		}

		else if ((Network::getID() == 2 && Network::didLost()) || (Network::getID() == 1 && !Network::didLost())) {
			currentPlayer = player2;
			currentPlayer->setTurn(true);
		}

		else {
			// Nothing to do
		}
	}
	changePlayer = false;
	this->endButton = new Button(
									new Sprite(SDLBase::resourcesPath + "endturn_2.png"),
									new Sprite(SDLBase::resourcesPath + "endturn_1.png"),
									new Sprite(SDLBase::resourcesPath + "endturn_3.png"),
									660,
									460);
	deltaEnd = 0;
	splashWon = new Sprite(SDLBase::resourcesPath + "youwon.bmp");
	splashWon->incNumRef();
	wonHandler = new FadeHandler(splashWon);
	splashLost = new Sprite(SDLBase::resourcesPath + "youlost.bmp");
	splashLost->incNumRef();
	lostHandler = new FadeHandler(splashLost);
	wonHandler->fadeOut(0,0.1);
	lostHandler->fadeOut(0,0.1);
	gameEnded = false;
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

void Map::render(float cameraX, float cameraY){
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

	if (currentPlayer) {
		currentPlayer->getHud()->render(0,0);
	}

	else {
		// Nothing to do
	}
	stringstream st;
	st << ((int)(currentPlayer->getStamina()));
	SDLBase::renderText(font, st.str(),color,720,60);

	if (currentPlayer) {
		if (currentPlayer->getId() == Network::getID()) {
			SDLBase::renderText(turn, "Your", color, 712, 140);
		}

		else {
			SDLBase::renderText(turn, "Opponent", color, 686, 140);
		}
	}

	else {
		// Nothing to do
	}

	endButton->render(0,0);
	splashWon->render(0,0);
	splashLost->render(0,0);

}

int Map::update(int dt) {
	InputManager* input;
	input = InputManager::getInstance();

	for (unsigned int i = 0; i < tiles.size(); i++) {
		tiles.at(i)->update(dt);
		if (tiles.at(i)->isClickable()) {
			tiles.at(i)->animateClickableTiles(dt);
		}

		else {
			// Nothing to do
		}
	}
	
	if (currentPlayer->isUsingSkill()) {
		if (input->isMousePressed(1)) {
			Tile* currentTile = getPressedTile();
			currentPlayer->setSkillDestTile(currentTile);
		}

		else {
			// Nothing to do
		}
	}

	else {
		// Nothing to do
	}

	player1->update(dt);
	player2->update(dt);

	deltaEnd += dt;
	mouseOver(endButton, input);
	mousePressed(endButton, input);
	this->endButton->update(dt);

	if (!currentPlayer->getWin()) {
		if (currentPlayer->getStamina() <= 0 && !changePlayer) {
			changePlayer = true;
		}

		if (changePlayer) {
			changeCurrentPlayer();
		}
	}

	else {
		AudioHandler * audio = AudioHandler::getInstance();
		if (!gameEnded) {
			gameEnded = true;
			Network::setFirstTime(false);
			if (currentPlayer->getId() == Network::getID()) {	
			 	audio->setEffect("youwon.wav");
			 	audio->playEffect(0);

				wonHandler->fadeIn(2,0.5);
				Network::setLost(false);
			}

			else {
				audio->setEffect("youlost.ogg");
			 	audio->playEffect(0);

				lostHandler->fadeIn(2,0.5);
				Network::setLost(true);
			}
		}

		else {
			// Nothing to do
		}

		currentPlayer->setTurn(false);
	}

	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i)->getBlock()) {
			if (tiles.at(i)->getBlock()->getDestroyedFinalBlock()) {
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

	wonHandler->update(dt);
	lostHandler->update(dt);
	return 0;
}

Tile * Map::getPressedTile() {
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


bool Map::isFirstRow(int index) {
	return (index < columns);
}

bool Map::isFirstColumn(int index) {
	return ((index % columns) == 0);
}

bool Map::isLastRow(int index) {
	return ((index + columns) > (columns*rows - 1));
}

bool Map::isLastColumn(int index) {
	return ((index % columns) == (columns - 1));
}

void Map::mousePressed(Button *bt, InputManager* input) {

	if ((input->isMousePressed(1)) && (bt->insideButton()) == 1) {
		bt->mousePressed(true);
		if (deltaEnd > 1000 && !currentPlayer->isPerformingAction() && currentPlayer->getId() == Network::getID() && !currentPlayer->isUsingSkill()) {
			deltaEnd = 0;
			changeCurrentPlayer();
			currentPlayer->sendMessage("EndTurn", "-1");
		}

		else {
			// Nothing to do
		}

	}

	else {
		bt->mousePressed(false);
	}
}

void Map::mouseOver(Button *bt, InputManager * input){
	bt->setMouseCoord(input->mousePosX(),input->mousePosY());
}

void Map::changeCurrentPlayer() {
	if (!currentPlayer->isPerformingAction() && !currentPlayer->isUsingSkill()) {
		AudioHandler * audio = AudioHandler::getInstance();
	 	audio->setEffect("passar_turno.ogg");
	 	audio->playEffect(0);
	 	if ((Network::getID()== 2 && currentPlayer->getId() == 1) || (Network::getID()==1 && currentPlayer->getId() == 2)) {
	 		tryToSpawnSand();
	 	}

	 	else {
	 		// Nothing to do
	 	}

		changePlayer = false;
		if (currentPlayer->getId() == 1) {
			currentPlayer = player2;
		}

		else {
			currentPlayer = player1;
		}

		player1->setStamina(player1->getInitialStamina());
		player2->setStamina(player2->getInitialStamina());
		player1->toogleTurn();
		player2->toogleTurn();
	}
}

void Map::tryToSpawnSand() {
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
		currentPlayer->spawnSand(msg);
		SDL_Delay(50);
	}

	else {
		// Nothing to do
	}
}

void Map::spawnSand(int id) {
	tiles.at(id)->createSandBlock();
}

Tile * Map::getTileWithIndex(int index) {
	return tiles.at(index);
}
