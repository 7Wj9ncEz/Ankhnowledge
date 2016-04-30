/*
 * SelectCharacterController.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#include "SelectCharacterController.h"

#include <sstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

SelectCharacterController::SelectCharacterController():GameObject(getX(),getY()) {
	splashSprite = new Sprite(SDLBase::resourcesPath + "Bg.png");
	splashSprite->incNumRef();
	p1Board = new Sprite(SDLBase::resourcesPath + "locked.png");
	p1Board->incNumRef();
	p2Board = new Sprite(SDLBase::resourcesPath + "locked.png");
	p2Board->incNumRef();
	board = new Sprite(SDLBase::resourcesPath + "charborder.png");
	board->incNumRef();
	boardAnimation = new Animation(44,72,board,0);
	vs = new Sprite(SDLBase::resourcesPath + "vs.png");
	vs->incNumRef();
	vsAnimation = new Animation(93,60,vs,0);
	zero = new Sprite(SDLBase::resourcesPath + "0.png");
	zero->incNumRef();
	one = new Sprite(SDLBase::resourcesPath + "1.png");
	one->incNumRef();
	two = new Sprite(SDLBase::resourcesPath + "2.png");
	two->incNumRef();
	three = new Sprite(SDLBase::resourcesPath + "3.png");
	three->incNumRef();
	four = new Sprite(SDLBase::resourcesPath + "4.png");
	four->incNumRef();
	five = new Sprite(SDLBase::resourcesPath + "5.png");
	five->incNumRef();
	alanFaceP1 = new Sprite(SDLBase::resourcesPath + "alanchoose.png");
	alanFaceP1->incNumRef();
	sutiFaceP1 = new Sprite(SDLBase::resourcesPath + "sutichoose2.png");
	sutiFaceP1->incNumRef();
	alanFaceP2 = new Sprite(SDLBase::resourcesPath + "alanchoose2.png");
	alanFaceP2->incNumRef();
	sutiFaceP2 = new Sprite(SDLBase::resourcesPath + "sutichoose.png");
	sutiFaceP2->incNumRef();

	alan = new HoverButton(new Sprite(SDLBase::resourcesPath + "adamselect.png"),0,0);
	suti = new HoverButton(new Sprite(SDLBase::resourcesPath + "sutiselect.png"),0,0);

	alan->setPosition(400-alan->getSprite()->getWidth(), 450);
	suti->setPosition(400+alan->getSprite()->getWidth(), 450);

	currentOnTop = -1;
	opponentOnTop = -1;
	currentPressed = -1;
	opponentPressed = -1;
	xBoard = -2000;
	yBoard = -2000;
	locked = true;
	change_scene = false;
	sendMessage("Loaded", "-1");

	timer = 5000;

}

SelectCharacterController::~SelectCharacterController() {
	splashSprite->decNumRef();
	p1Board->decNumRef();
	p2Board->decNumRef();
	board->decNumRef();
	alanFaceP1->decNumRef();
	sutiFaceP1->decNumRef();
	alanFaceP2->decNumRef();
	sutiFaceP2->decNumRef();
	zero->decNumRef();
	one->decNumRef();
	two->decNumRef();
	three->decNumRef();
	four->decNumRef();
	five->decNumRef();

	delete alan;
	delete suti;
}

void SelectCharacterController::render(float camera_x, float camera_y){
	splashSprite->render(0,0);

	if(	(Network::getID() == 1 && (currentOnTop == 1 || currentPressed == 1)) ||
		(Network::getID() == 2 && (opponentOnTop == 1 || opponentPressed == 1)))
	{
		alanFaceP1->render(150,25);
	}
		//alanFaceP1->render(100,150);

	if(	(Network::getID() == 1 && (currentOnTop == 2 || currentPressed == 2)) ||
		(Network::getID() == 2 && (opponentOnTop == 2 || opponentPressed == 2)))
	{
		sutiFaceP1->render(150,25);
	}
		//sutiFaceP1->render(100,150);

	if(	(Network::getID() == 2 && (currentOnTop == 1 || currentPressed == 1)) ||
		(Network::getID() == 1 && (opponentOnTop == 1 || opponentPressed == 1)))
	{
		alanFaceP2->render(675-alanFaceP2->getWidth(),25);
	}
		//alanFaceP2->render(700-alanFaceP2->getWidth(),150);

	if(	(Network::getID() == 2 && (currentOnTop == 2 || currentPressed == 2)) ||
		(Network::getID() == 1 && (opponentOnTop == 2 || opponentPressed == 2)))
	{
		sutiFaceP2->render(675-sutiFaceP2->getWidth(),25);
	}
		//sutiFaceP2->render(700-sutiFaceP2->getWidth(),150);

	if(	(Network::getID() == 1 && (currentPressed != -1)) ||
		(Network::getID() == 2 && (opponentPressed != -1)))
	{
		p1Board->render(150,25);
	}
		//p1Board->render(100,150);

	if(	(Network::getID() == 2 && (currentPressed != -1)) ||
		(Network::getID() == 1 && (opponentPressed != -1)))
	{
		p2Board->render(675-alanFaceP2->getWidth(),25);
	}
		//p2Board->render(700-alanFaceP2->getWidth(),150);

	alan->render(0,0);
	suti->render(0,0);
	boardAnimation->animate(150, xBoard, yBoard);
	vsAnimation->animate(150, 360, 150);

	stringstream sstimer;
	sstimer << (int)this->timer/1000;
	if(sstimer.str() == "5")
	{
		five->render(375,325);
	}
	else if(sstimer.str() == "4")
	{
		four->render(375,325);
	}
	else if(sstimer.str() == "3")
	{
		three->render(375,325);
	}
	else if(sstimer.str() == "2")
	{
		two->render(375,325);
	}
	else if(sstimer.str() == "1")
	{
		one->render(375,325);
	}
	else if(sstimer.str() == "0")
	{
		zero->render(375,325);
	}

}

int SelectCharacterController::update(int dt){
	alan->update(dt);
	suti->update(dt);

	if(!locked)
	{
		if(currentPressed == -1 ||opponentPressed == -1)
		{
		if(timer > 0)
			timer -= dt;
		else
			timer = 0;
		}
		if(timer == 0 && currentPressed == -1)
		{
			if(currentOnTop == -1)
			{
				srand (time(NULL));
				int random = (rand()%2)+1;
				currentPressed = random;
				if(random == 1)
				{
					sendMessage("OnPressAlan", "-1");
				}
				else if(random == 2)
				{
					sendMessage("OnPressSuti", "-1");
				}
			}else
			{
				if(currentOnTop == 1)
				{
					currentPressed = 1;
					sendMessage("OnPressAlan", "-1");
				}
				else if(currentOnTop == 2)
				{
					currentPressed = 2;
					sendMessage("OnPressSuti", "-1");
				}
			}
		}

		if(timer > 0)
			{
			if(alan->isOnTop() && currentPressed == -1 && currentOnTop != 1)
			{
				currentOnTop = 1;
				xBoard = alan->getX();
				yBoard = alan->getY();
				sendMessage("OnTopAlan", "-1");
			}

			if(suti->isOnTop() && currentPressed == -1 && currentOnTop != 2)
			{
				currentOnTop = 2;
				xBoard = suti->getX();
				yBoard = suti->getY();
				sendMessage("OnTopSuti", "-1");
			}


			if(alan->is_pressed() && currentPressed == -1)
			{
				currentPressed = 1;
				xBoard = alan->getX();
				yBoard = alan->getY();
				sendMessage("OnPressAlan", "-1");
			}
			if(suti->is_pressed() && currentPressed == -1)
			{
				currentPressed = 2;
				xBoard = suti->getX();
				yBoard = suti->getY();
				sendMessage("OnPressSuti", "-1");
			}
		}
	}

	if(currentPressed != -1 && opponentPressed != -1 && !change_scene)
	{
		change_scene = true;
		if(Network::getID() == 1)
		{
			Network::player1Selection = currentPressed;
			Network::player2Selection = opponentPressed;
		}
		if(Network::getID() == 2)
		{
			Network::player1Selection = opponentPressed;
			Network::player2Selection = currentPressed;
		}
		if(GameManager::currentScene->change_scene("SceneSelectMap") == 1)
							GameManager::fadeScreen->fade_in(1,2);
	}

	this->boardAnimation->update(dt, true, 0, false);
	this->vsAnimation->update(dt, true, 0, false);

	receiveMessage();
	return 0;

}

void SelectCharacterController::receiveMessage()
{
	string message = Network::readMessage();
	if(message == "")
		return;

	istringstream iss(message);

	string action;
	string info;

	iss >> action;
	iss >> info;


	if(action == "OnTopAlan")
	{
		opponentOnTop = 1;
	}
	else
	if(action == "OnTopSuti")
	{
		opponentOnTop  = 2;
	}
	else
	if(action == "OnPressAlan")
	{
		opponentPressed = 1;
	}
	if(action == "OnPressSuti")
	{
		opponentPressed = 2;
	}
	if(action == "Loaded")
	{
		locked = false;
	}
}

void SelectCharacterController::sendMessage(string action, string info)
{
	string msg = action + " " + info;
	Network::sendMessage(msg);
}

string SelectCharacterController::intToString(int intenger)
{
	string st;
	ostringstream convert;
	convert << intenger;
	st = convert.str();
	return st;
}

