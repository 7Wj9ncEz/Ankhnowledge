/*
 * SelectCharacterController.h
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#ifndef SELECTCHARACTERCONTROLLER_H_
#define SELECTCHARACTERCONTROLLER_H_

#include "GameObject.h"
#include "HoverButton.h"
#include "Sprite.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <vector>
#include "Network.h"
#include "Animation.h"

using namespace std;

class SelectCharacterController:public GameObject {
public:
	SelectCharacterController();
	virtual ~SelectCharacterController();
	void render(float camera_x, float camera_y);
	int update(int dt);
	void receive_message();
	void send_message(string action, string info);
	string intToString(int intenger);

private:
	Sprite* splashSprite, *p1Board, *p2Board, *board, *vs;
	Sprite* five, *four, *three, *two, *one, *zero;
	Sprite* alanFaceP1, *sutiFaceP1, *alanFaceP2, *sutiFaceP2;
	Animation* boardAnimation, *vsAnimation;
	HoverButton* alan, *suti;
	int currentOnTop, opponentOnTop;
	int currentPressed, opponentPressed;
	float xBoard, yBoard;
	bool locked, change_scene;
	float timer;
};

#endif /* SELECTCHARACTERCONTROLLER_H_ */
