/*
 * OptionsController.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#include "OptionsController.h"
#include "AudioHandler.h"
#include <iostream>
#include <sstream>

OptionsController::OptionsController():GameObject(getX(),getY()) {
	this->back_1 = new Sprite(SDLBase::resourcesPath + "back_1.png");
	this->back_2 = new Sprite(SDLBase::resourcesPath + "back_2.png");
	this->back_3 = new Sprite(SDLBase::resourcesPath + "back_3.png");
	this->back = new Button(back_1,back_2,back_3,500,500);
	this->sliderBar = new Sprite(SDLBase::resourcesPath + "slider_bar.png");
	this->sliderButton = new Sprite(SDLBase::resourcesPath + "slider_button.png");
	bgVolume = new Slider(sliderButton,sliderBar,400,230);
	soundEffect = new Slider(sliderButton,sliderBar,400,310);
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "options.png");
	input = InputManager::getInstance();
	SDLBase::initializeSDLTTF();
	const SDL_Color temp = {0, 0, 0, 255};
	color = temp;
	string font_path = SDLBase::resourcesPath + "quicksandbold.ttf";
	font = SDLBase::loadFont(font_path.c_str(),40);
	this->musicVolume = ((int)(100*bgVolume->calculateValue()));
	this->effectVolume = ((int)(100*soundEffect->calculateValue()));

}

OptionsController::~OptionsController() {
	// TODO Auto-generated destructor stub
}

void OptionsController::render(float camera_x, float camera_y){
	this->splashSprite->render(0,0);
	this->back->render(0,0);
	this->bgVolume->render(0,0);
	this->soundEffect->render(0,0);

	int currentMusicVolume = ((int)(100*bgVolume->calculateValue()));
	if (currentMusicVolume != this->musicVolume)
	{
		AudioHandler * audio = AudioHandler::getInstance();
		audio->set_music_volume(currentMusicVolume);
		this->musicVolume = currentMusicVolume;
		//audio->set_effect_volume(this->effectVolume);
	}

	int currentEffectVolume = ((int)(100*soundEffect->calculateValue()));
	if (currentEffectVolume != this->effectVolume)
	{
		AudioHandler * audio = AudioHandler::getInstance();
		audio->set_effect_volume(currentEffectVolume);
		audio->set_effect("sand_action.wav");
		audio->play_effect(0);
		this->effectVolume = currentEffectVolume;
	}

	stringstream ssbgvolume;
	ssbgvolume << this->musicVolume;
	SDLBase::renderText(font, ssbgvolume.str() + "%" ,color,720,220);
	
	stringstream sssoundeffect;
	sssoundeffect << this->effectVolume;
	SDLBase::renderText(font, sssoundeffect.str() + "%" ,color,720,300);


}

int OptionsController::update(int dt){
	mouse_ouver(back);
	mouse_pressed(back,"SceneMainMenu");
	this->back->update(dt);
	if (soundEffect->getSlideButton()== false)
	{	
		this->bgVolume->update(dt);
	}
	if (bgVolume->getSlideButton() == false)
	{	
		this->soundEffect->update(dt);
	}
	return 0;
}

void OptionsController::mouse_ouver(Button *bt){
	bt->setMouseCoord(input->mouse_pos_x(),input->mouse_pos_y());
}

void OptionsController::mouse_pressed(Button *bt,string scene){

	if (input->is_mouse_pressed(1) && bt->inside_button() == 1)
	{
		bt->mouse_pressed(true);

		if (bt->getChangeScene())
		{
			change_scene(scene);
		}
	}
	else
	{
		bt->mouse_pressed(false);
	}
}

void OptionsController::change_scene(string nextScene){
	if (GameManager::currentScene->change_scene(nextScene) == 1)
		GameManager::fadeScreen->fade_in(1,0.2);
}
