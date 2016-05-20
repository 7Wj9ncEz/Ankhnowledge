/*
 * MessageBox.cpp
 *
 *  Created on: Dec 3, 2013
 *      Author: al
 */

#include "MessageBox.h"

using namespace std;

MessageBox::MessageBox(Sprite * box, string buttonName, float x, float y):GameObject(getX(),getY()){
	this->box = box;	
	Sprite* confirm_1 = new Sprite(SDLBase::resourcesPath + buttonName + "_1.png");
	Sprite* confirm_2 = new Sprite(SDLBase::resourcesPath + buttonName + "_2.png");
	Sprite* confirm_3 = new Sprite(SDLBase::resourcesPath + buttonName + "_3.png");
	this->confirm = new Button(confirm_1,confirm_2,confirm_3,x + 180,y + box->getHeight() - 40);
	this->cancel = 0;
	input = InputManager::getInstance();
	this->confirmPress = false;
	this->cancelPress = false;
	this->boxInput = 0;
	this->x = x;
	this->y = y;
	this->renderCursorAnim = false;
}

MessageBox::MessageBox(Sprite * box, string buttonName1, string buttonName2, float x, float y):GameObject(getX(),getY()){

	this->box = box;
	Sprite* confirm_1 = new Sprite(SDLBase::resourcesPath + buttonName1 + "_1.png");
	Sprite* confirm_2 = new Sprite(SDLBase::resourcesPath + buttonName1 + "_2.png");
	Sprite* confirm_3 = new Sprite(SDLBase::resourcesPath + buttonName1 + "_3.png");
	this->confirm = new Button(confirm_1,confirm_2,confirm_3,x + 200,y + box->getHeight() - 40);
	Sprite* cancel_1 = new Sprite(SDLBase::resourcesPath + buttonName2 + "_1.png");
	Sprite* cancel_2 = new Sprite(SDLBase::resourcesPath + buttonName2 + "_2.png");
	Sprite* cancel_3 = new Sprite(SDLBase::resourcesPath + buttonName2 + "_3.png");
	this->cancel = new Button(cancel_1,cancel_2,cancel_3,x + 50,y + box->getHeight() - 40);
	input = InputManager::getInstance();
	this->confirmPress = false;
	this->cancelPress = false;
	this->boxInput = 0;
	this->x = x;
	this->y = y;
	this->renderCursorAnim = false;
	this->incCursor = 0;
}

MessageBox::MessageBox(Sprite * box, Sprite* boxInput, string buttonName, Animation* animation, float x, float y):GameObject(getX(),getY()){
	this->box = box;	
	this->boxInput = boxInput;
	this->cursor = animation;
	Sprite* confirm_1 = new Sprite(SDLBase::resourcesPath + buttonName + "_1.png");
	Sprite* confirm_2 = new Sprite(SDLBase::resourcesPath + buttonName + "_2.png");
	Sprite* confirm_3 = new Sprite(SDLBase::resourcesPath + buttonName + "_3.png");
	this->confirm = new Button(confirm_1,confirm_2,confirm_3,x + 240,y + box->getHeight() - 40);
	this->cancel = 0;
	input = InputManager::getInstance();
	this->confirmPress = false;
	this->cancelPress = false;
	this->x = x;
	this->y = y;
	this->boxInputX = x + box->getWidth()/2 - boxInput->getWidth()/2;
	this->boxInputY = y + 25;
	this->renderCursorAnim = false;

}

MessageBox::~MessageBox(){

}


void MessageBox::render(float camera_x, float camera_y){
	box->render(x,y);
	if (boxInput)
		boxInput->render(this->boxInputX,this->boxInputY + 30);	
	if (confirm)
		confirm->render(0,0);

	if (cancel)
		cancel->render(0,0);
	if (renderCursorAnim)
		this->cursor->animate(100, boxInputX + 9 + incCursor,boxInputY + 30);
	
}

int MessageBox::update(int dt){
	
	if (confirm)
	{
		mouse_ouver(confirm);
		buttonPressed(confirm,"confirm");
		confirm->update(dt);
		
	}

	if (cancel)
	{
		mouse_ouver(cancel);
		buttonPressed(cancel,"cancel");
		cancel->update(dt);
	}
	if (renderCursorAnim)
		cursor->update(dt, true,0,0);

return 0;
}

bool MessageBox::isInsideBox(){
	return ((input->mouse_pos_x() > this->boxInputX) && (input->mouse_pos_x() < (this->boxInputX + this->boxInput->getWidth())) && (input->mouse_pos_y() > this->boxInputY + 25) && (input->mouse_pos_y() < (this->boxInputY + 25 + boxInput->getHeight())));
}

void MessageBox::buttonPressed(Button *bt, string buttonName){

if((input->is_mouse_pressed(1)) && (bt->inside_button()) == 1)
{
	bt->mouse_pressed(true);
	if (buttonName == "confirm")
		confirmPress = true;
	else
		cancelPress = true;
	bt->setChangeSprite(1);
}
else {
	bt->mouse_pressed(false);
}
 

}

void MessageBox::deactivateCancel(){
	this->cancelPress = false;
}

void MessageBox::activateCursor(){
	this->renderCursorAnim = true;
}

void MessageBox::deactivateConfirm(){
	this->confirmPress = false;
}

void MessageBox::deactivateCursor(){
	this->renderCursorAnim = false;
}

void MessageBox::mouse_ouver(Button *bt){
	bt->setMouseCoord(input->mouse_pos_x(),input->mouse_pos_y());
	if((bt->inside_button() == 1))		
		bt->setChangeSprite(1);

}

void MessageBox::renderCursor(){
	this->renderCursorAnim = true;
}

bool MessageBox::confirm_pressed(){
	return this->confirmPress;
}

bool MessageBox::cancelPressed(){
	return this->cancelPress;
}

void MessageBox::increaseCursor(float inc){
	incCursor += inc;
}

void MessageBox::decreaseCursor(float inc){
	float tempInc = incCursor;	
	incCursor -= inc;
	if (incCursor < 0)
		incCursor = tempInc;
}
