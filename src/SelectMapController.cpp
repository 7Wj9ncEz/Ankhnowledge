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
	rightButton->setPosition(800 - rightButton->getSprite()->getWidth()-120,250);

	for(unsigned int i = 0; i < mapButtons.size(); i++)
	{
		mapButtons.at(i)->setPosition(800/2-mapButtons.at(i)->getSprite()->getWidth()/2 + i*540,100);
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
	sendMessage("Loaded", "-1");
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
		if(i == 0)
			mapNames.at(i)->render(mapButtons.at(i)->getX()+60, 50);
		else
			mapNames.at(i)->render(mapButtons.at(i)->getX()+95, 50);
	}

	boardAnimation->animate(175, boardX+5, boardY);
	leftButton->render(0,0);
	rightButton->render(0,0);
}

int SelectMapController::update(int dt){
	leftButton->update(dt);
	rightButton->update(dt);

	if(!locked)
	{
		if((Network::isFirstTime() && Network::getID() == 1) || Network::didLost())
		{
			for(unsigned int i = 0; i < mapButtons.size(); i++)
			{
				mapButtons.at(i)->update(dt);
			}

			onTopBoard = false;
			for(unsigned int i = 0; i < mapButtons.size(); i++)
			{

				mapButtons.at(i)->update(dt);

				if(mapButtons.at(i)->isPressed() && currentMap == i)
				{
					mapselected = i;
					cout<<"aqui"<<i<<endl;
				}

				if(mapButtons.at(i)->isOnTop() && acumulated2 >500 && currentMap == i)
				{
					boardX = mapButtons.at(i)->getX();
					boardY = mapButtons.at(i)->getY();
					onTopBoard = true;
				}
			}

			if(leftButton->isPressed() && changingMap == 0 && currentMap > 0)
			{
				moveLeft();
				sendMessage("Left", "-1");
			}

			if(rightButton->isPressed() && changingMap == 0 && currentMap < 4)
			{
				moveRight();
				sendMessage("Right", "-1");
			}
		}
	}

	this->boardAnimation->update(dt, true, 0, false);

	changeMap(dt);
	if(!onTopBoard)
	{
		boardX = -2000;
		boardY = -2000;
	}
	changeScene();

	receiveMessage();
	return 0;
}

void SelectMapController::changeScene(){
	if(mapselected == -1)
		return;

	cout<<"Mapa selecionado"<< mapselected <<endl;
	chooseMap(mapselected);
	sendMessage("ChoseMap", intToString(mapselected));
	mapselected = -1;
}

void SelectMapController::changeMap(int dt)
{

	if(acumulated2 < 2000)
		acumulated2 += dt;

	if(changingMap != 0)
	{
		for(unsigned int i = 0; i < mapButtons.size(); i++)
		{
			mapButtons.at(i)->setPosition((mapButtons.at(i)->getX()+ ((mapButtons.at(i)->begin-(540*changingMap)) - mapButtons.at(i)->getX())*dt/100),100);
		}

		acumulated += dt;

		if(acumulated > 1000)
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
	if(index == 0)
		{
			if(GameManager::currentScene->changeScene("ScenePhaseOne") == 1)
					GameManager::fadeScreen->fadeIn(1,0.2);
		}
		else if(index == 1)
		{
			if(GameManager::currentScene->changeScene("ScenePhaseTwo") == 1)
					GameManager::fadeScreen->fadeIn(1,0.2);
		}
		else if(index == 2)
		{
			if(GameManager::currentScene->changeScene("ScenePhaseThree") == 1)
					GameManager::fadeScreen->fadeIn(1,0.2);
		}
		else if(index == 3)
		{
			if(GameManager::currentScene->changeScene("ScenePhaseFour") == 1)
					GameManager::fadeScreen->fadeIn(1,0.2);
		}
		else if(index == 4)
		{
			if(GameManager::currentScene->changeScene("ScenePhaseFive") == 1)
					GameManager::fadeScreen->fadeIn(1,0.2);
		}
}

void SelectMapController::receiveMessage()
{
	string message = Network::readMessage();
	if(message == "")
		return;

	istringstream iss(message);

	string action;
	string info;

	iss >> action;
	iss >> info;


	if(action == "Left")
	{
		moveLeft();
	}
	else
	if(action == "Right")
	{
		moveRight();
	}
	else
	if(action == "ChoseMap")
	{
		chooseMap(atoi(info.c_str()));
	}
	if(action == "Loaded")
	{
		locked = false;
	}
}

void SelectMapController::sendMessage(string action, string info)
{
	string msg = action + " " + info;
	Network::sendMessage(msg);
}

string SelectMapController::intToString(int intenger)
{
	string st;
	ostringstream convert;
	convert << intenger;
	st = convert.str();
	return st;
}

