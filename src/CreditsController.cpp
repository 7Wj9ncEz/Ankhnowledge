/*
 * CreditsController.cpp
 *
 * Class responsible by creating Game Menu's Credit Scene.
 *
 */

#include "CreditsController.h"
#include <iostream>

CreditsController::CreditsController():GameObject(getX(),getY()) {
	this->back_1 = new Sprite(SDLBase::resourcesPath + "back_1.png");
	this->back_2 = new Sprite(SDLBase::resourcesPath + "back_2.png");
	this->back_3 = new Sprite(SDLBase::resourcesPath + "back_3.png");
	this->back = new Button(back_1,back_2,back_3,500,500);
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "credits.png");
	input = InputManager::getInstance();

}

CreditsController::~CreditsController() {
	// TODO Auto-generated destructor stub
}

void CreditsController::render(float camera_x, float camera_y){
	this->splashSprite->render(0,0);
	this->back->render(0,0);
}

int CreditsController::update(int detective){
	mouse_ouver(back);
	mouse_pressed(back,"SceneMainMenu");
	this->back->update(detective);
	return 0;
}

void CreditsController::mouse_ouver(Button *bt){
	bt->setMouseCoord(input->mouse_pos_x(),input->mouse_pos_y());
}

void CreditsController::mouse_pressed(Button *bt,string scene){

	if (input->is_mouse_pressed(1) && bt->inside_button() == 1) {
		bt->mouse_pressed(true);

		if (bt->getChangeScene()) {
			change_scene(scene);
		}

		else {
			// Nothing to do
		}
	}

	else {
		bt->mouse_pressed(false);
	}
}

/**
 *

void CreditsController::change_scene(string nextScene){
	if (GameManager::current_scene->change_scene(nextScene) == 1) {
		GameManager::fade_screen->fade_in(1,0.2);
	}

	else {
		// Nothing to do
	}
}
**/
