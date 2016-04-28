/*
 * Button.h
 *
 *  Created on: Oct 9, 2013
 *      Author: al
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "GameObject.h"
#include "Sprite.h"

class Button:public GameObject {
public:
	Button(Sprite* sprite1,Sprite* sprite2,Sprite* sprite3, float x,float y);
	void render(float camera_x,float camera_y);
	int update(int dt);
	void setMouseCoord(float coordinateX, float coordinateY);
	void mousePressed(bool isPressed);
	bool insideButton();
	bool getChangeScene();
	virtual ~Button();
	void setChangeSprite(bool changeSprite);

private:
	Sprite* sprite1,*sprite2,*sprite3,*currentSprite;
	float x,y,mouseX,mouseY;
	bool isPressed;
	bool changeScene;
	bool changeSprite;

};

#endif /* BUTTON_H_ */
