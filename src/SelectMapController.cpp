/*
 * SelectSceneController.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#include "SelectMapController.h"
#include <sstream>

SelectMapController::SelectMapController():GameObject(getX(),getY()) {

	mapButtons.push_back(new HoverButton(new Sprite(SDLBase::resourcesPath + "map1mock.png"),0,0));
	mapButtons.push_back(new HoverButton(new Sprite(SDLBase::resourcesPath + "map2mock.png"),0,0));
	mapButtons.push_back(new HoverButton(new Sprite(SDLBase::resourcesPath + "map3mock.png"),0,0));
	mapButtons.push_back(new HoverButton(new Sprite(SDLBase::resourcesPath + "map4mock.png"),0,0));
	mapButtons.push_back(new HoverButton(new Sprite(SDLBase::resourcesPath + "map5mock.png"),0,0));
	mapNames.push_back(new Sprite(SDLBase::resourcesPath + "map1name.png"));
	mapNames.push_back(new Sprite(SDLBase::resourcesPath + "map2name.png"));
	mapNames.push_back(new Sprite(SDLBase::resourcesPath + "map3name.png"));
	mapNames.push_back(new Sprite(SDLBase::resourcesPath + "map4name.png"));
	mapNames.push_back(new Sprite(SDLBase::resourcesPath + "map5name.png"));

	for(unsigned int i = 0; i < mapNames.size(); i++)
	{
		mapNames.at(i)->incNumRef();
	}

	leftButton = new HoverButton(new Sprite(SDLBase::resourcesPath + "left.png"),120,250);
	rightButton = new HoverButton(new Sprite(SDLBase::resourcesPath + "right.png"),0,0);
	rightButton->setPosition(800 - rightButton->get_sprite()->getWidth()-120,250);

	for(unsigned int i = 0; i < mapButtons.size(); i++)
	{
		mapButtons.at(i)->setPosition(800/2-mapButtons.at(i)->get_sprite()->getWidth()/2 + i*540,100);
	}


	this->splashSprite = new Sprite(SDLBase::resourcesPath + "mapselectbg.png");
	this->splashSprite->incNumRef();
	this->board = new Sprite(SDLBase::resourcesPath + "mapborder.png");
	this->board->incNumRef();
	board->incNumRef();
	boardAnimation = new Animation(340,460,board,0);
	boardX = -2000;
	boardY = -2000;
	mapselected = -1;
	input = InputManager::getInstance();
	currentMap = 0;
	locked = false;
	changingMap = 0;
	send_message("Loaded", "-1");
}

SelectMapController::~SelectMapController() {

	this->splashSprite->decNumRef();
	this->splashSprite = 0;
	this->board->decNumRef();
	this->board = 0;

	for(unsigned int i = 0; i < mapButtons.size(); i++)
	{
		delete mapButtons.at(i);
	}

	for(unsigned int i = 0; i < mapNames.size(); i++)
	{
		mapNames.at(i)->decNumRef();
	}
}

void SelectMapController::render(float camera_x, float camera_y){
	this->splashSprite->render(0,0);
	for(unsigned int i = 0; i < mapButtons.size(); i++)
	{
		mapButtons.at(i)->render(0,0);
	}
	for(unsigned int i = 0; i < mapNames.size(); i++)
	{
		if (i == 0)
			mapNames.at(i)->render(mapButtons.at(i)->getX()+60, 50);
		else
			mapNames.at(i)->render(mapButtons.at(i)->getX()+95, 50);
	}

	boardAnimation->animate(175, boardX+5, boardY);
	leftButton->render(0,0);
	rightButton->render(0,0);
}

int SelectMapController::update(int detective){
	leftButton->update(detective);
	rightButton->update(detective);

	if(!locked)
	{
		if((Network::is_first_time() && Network::get_id() == 1) || Network::did_lose())
		{
			for(unsigned int i = 0; i < mapButtons.size(); i++)
			{
				mapButtons.at(i)->update(detective);
			}

			onTopBoard = false;
			for(unsigned int i = 0; i < mapButtons.size(); i++)
			{

				mapButtons.at(i)->update(detective);

				if (mapButtons.at(i)->is_pressed() && currentMap == i)
				{
					mapselected = i;
					cout<<"aqui"<<i<<endl;
				}

				if (mapButtons.at(i)->is_on_top() && acumulated2 >500 && currentMap == i)
				{
					boardX = mapButtons.at(i)->getX();
					boardY = mapButtons.at(i)->getY();
					onTopBoard = true;
				}
			}

			if (leftButton->is_pressed() && changingMap == 0 && currentMap > 0)
			{
				moveLeft();
				send_message("Left", "-1");
			}

			if (rightButton->is_pressed() && changingMap == 0 && currentMap < 4)
			{
				moveRight();
				send_message("Right", "-1");
			}
		}
	}

	this->boardAnimation->update(detective, true, 0, false);

	changeMap(detective);
	if(!onTopBoard)
	{
		boardX = -2000;
		boardY = -2000;
	}
	change_scene();

	receive_message();
	return 0;
}

void SelectMapController::change_scene(){
	if (mapselected == -1)
		return;

	cout<<"Mapa selecionado"<< mapselected <<endl;
	chooseMap(mapselected);
	send_message("ChoseMap", intToString(mapselected));
	mapselected = -1;
}

void SelectMapController::changeMap(int detective)
{

	if (acumulated2 < 2000)
		acumulated2 += detective;

	if (changingMap != 0)
	{
		for(unsigned int i = 0; i < mapButtons.size(); i++)
		{
			mapButtons.at(i)->setPosition((mapButtons.at(i)->getX()+ ((mapButtons.at(i)->begin-(540*changingMap)) - mapButtons.at(i)->getX())*detective/100),100);
		}

		acumulated += detective;

		if (acumulated > 1000)
			changingMap = 0;
	}
}

void SelectMapController::moveLeft()
{
	changingMap = -1;
	for(unsigned int i = 0; i < mapButtons.size(); i++)
	{
			mapButtons.at(i)->begin = mapButtons.at(i)->getX();
	}
	acumulated = 0;
	acumulated2 = 0;
	currentMap--;
}

void SelectMapController::moveRight()
{

	changingMap = 1;
	for(unsigned int i = 0; i < mapButtons.size(); i++)
	{
			mapButtons.at(i)->begin = mapButtons.at(i)->getX();
	}
	acumulated = 0;
	acumulated2 = 0;
	currentMap++;
}

void SelectMapController::chooseMap(int index)
{
	if (index == 0)
		{
			if (GameManager::current_scene->change_scene("ScenePhaseOne") == 1)
					GameManager::fade_screen->fade_in(1,0.2);
		}
		else if (index == 1)
		{
			if (GameManager::current_scene->change_scene("ScenePhaseTwo") == 1)
					GameManager::fade_screen->fade_in(1,0.2);
		}
		else if (index == 2)
		{
			if (GameManager::current_scene->change_scene("ScenePhaseThree") == 1)
					GameManager::fade_screen->fade_in(1,0.2);
		}
		else if (index == 3)
		{
			if (GameManager::current_scene->change_scene("ScenePhaseFour") == 1)
					GameManager::fade_screen->fade_in(1,0.2);
		}
		else if (index == 4)
		{
			if (GameManager::current_scene->change_scene("ScenePhaseFive") == 1)
					GameManager::fade_screen->fade_in(1,0.2);
		}
}

void SelectMapController::receive_message()
{
	string message = Network::read_message();
	if (message == "")
		return;

	istringstream iss(message);

	string action;
	string info;

	iss >> action;
	iss >> info;


	if (action == "Left")
	{
		moveLeft();
	}
	else
	if (action == "Right")
	{
		moveRight();
	}
	else
	if (action == "ChoseMap")
	{
		chooseMap(atoi(info.c_str()));
	}
	if (action == "Loaded")
	{
		locked = false;
	}
}

void SelectMapController::send_message(string action, string info)
{
	string msg = action + " " + info;
	Network::send_message(msg);
}

string SelectMapController::intToString(int intenger)
{
	string st;
	ostringstream convert;
	convert << intenger;
	st = convert.str();
	return st;
}

