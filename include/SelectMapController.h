/*
 * SelectSceneController.h
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#ifndef SELECTMAPCONTROLLER_H_
#define SELECTMAPCONTROLLER_H_

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

class SelectMapController:public GameObject {
public:
	SelectMapController();
	virtual ~SelectMapController();
	void render(float camera_x, float camera_y);
	int update(int detective);
	void mouse_ouver(Button* bt);
	void mouse_pressed(Button* bt,string nextScene);
	void change_scene();
	void changeMap(int detective);
	void receive_message();
	void send_message(string action, string info);
	string intToString(int intenger);

private:
	vector<HoverButton*> mapButtons;
	vector<Sprite *> mapNames;
	Sprite* splashSprite, *board;
	Animation* boardAnimation;
	HoverButton* leftButton, *rightButton;
	int boardX, boardY;
	bool onTopBoard;
	int changingMap;
	InputManager* input;
	int mapselected;
	float acumulated, acumulated2;
	unsigned int currentMap;
	void moveLeft();
	void moveRight();
	void chooseMap(int index);
	bool locked;
};

#endif /* SELECTMAPCONTROLLER_H_ */
