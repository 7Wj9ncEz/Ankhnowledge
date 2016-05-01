/*
 * MainMenuButHandler.h
 *
 *  Created on: Oct 9, 2013
 *      Author: al
 */

#ifndef MAINMENUBUTHANDLER_H_
#define MAINMENUBUTHANDLER_H_
#include "GameObject.h"
#include "Button.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameManager.h"
#include "MessageBox.h"
#include "Animation.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class MainMenuButHandler:public GameObject {
public:
	MainMenuButHandler();
	virtual ~MainMenuButHandler();
	void render(float camera_x, float camera_y);
	int update(int dt);
	void mouse_ouver(Button* bt);
	void mouse_pressed(Button* bt,string nextScene);
	void change_scene(string nextScene);
	void renderConnect();
	void renderDisconnect();
	void renderWaiting();
	void updateConnect(int dt);
	void updateDisconnect(int dt);
	void updateWaiting(int dt);
	bool isInsideBox(MessageBox* messageBox);
	void readInput();
	void backspace();

private:
	Button* hostButton,* connectButton, *optionsButton, *creditsButton,*quitButton,*bt6,*bt7,*bt8;
	Sprite* bt1_1,*bt1_2,*bt1_3;
	Sprite* bt2_1,*bt2_2,*bt2_3;
	Sprite *bt3_1,*bt3_2,*bt3_3;
	Sprite *bt4_1,*bt4_2,*bt4_3;
	Sprite *bt5_1,*bt5_2,*bt5_3,*splashSprite;
	Sprite *bt6_1,*bt6_2,*bt6_3;
	Sprite *bt8_1,*bt8_2,*bt8_3;
	MessageBox *waitingBox, *connectBox,*disconnectBox;
	InputManager* input;
	Animation* animation, *waitAnim;
	Sprite* box,*boxInput,*bg,*cursor,*waiting,*loading,*disconnect;
	float boxInputX, boxInputY,boxX,boxY;
	SDL_Color color;
	TTF_Font *font;
	bool read,tryToConnect,clickOtherButtons,send_message,host, thread, renderConnectError;
	string message;
	int sizeMessage;
};

#endif /* MAINMENUBUTHANDLER_H_ */
