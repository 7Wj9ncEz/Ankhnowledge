/*
 * MessageBox.h
 *
 *  Created on: Dec 3, 2013
 *      Author: al
 */

#ifndef MESSAGEBOX_H_
#define MESSAGEBOX_H_
#include "GameObject.h"
#include "Button.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Animation.h"
#include <string>
#include <iostream>

class MessageBox:public GameObject {
public:
	MessageBox(Sprite * box, string buttonName, float x, float y);
	MessageBox(Sprite * box, string buttonName1, string buttonName2, float x, float y);
	MessageBox(Sprite * box, Sprite* boxInput, string buttonName, Animation* animation, float x, float y);
	virtual ~MessageBox();
	void render(float camera_x, float camera_y);
	int update(int dt);
	void buttonPressed(Button *button, string buttonName);
	void mouse_ouver(Button *bt);
	bool confirm_pressed();
	bool cancelPressed();
	void deactivateCancel();
	void deactivateConfirm();
	bool isInsideBox();
	void renderCursor();
	void deactivateCursor();
	void activateCursor();
	void increaseCursor(float inc);
	void decreaseCursor(float inc);

private:

	Button* confirm, *cancel;
	Sprite* box, * boxInput;
	Animation* cursor;
	InputManager *input;
	bool confirmPress, cancelPress,renderCursorAnim;
	float x,y,boxInputX,boxInputY,incCursor;
}; 

#endif /* MESSAGEBOX_H_ */
