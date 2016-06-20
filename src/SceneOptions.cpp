/*
 * SceneOptions.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#include <iostream>
#include "SceneOptions.h"

SceneOptions::SceneOptions(string scene_name) : Scene (scene_name)  {
	this->sound = new Sprite(SDLBase::resourcesPath + "somred.png");
	this->sound->incNumRef();
	this->soundAnimation = new Animation(50,50,sound,0);
}

SceneOptions::~SceneOptions()
{
	this->sound->decNumRef();
	this->sound = 0;
}

void SceneOptions::Enter()
{
	this->oc = new OptionsController();
	this->addGameObject(oc);

	GameManager::fade_screen->fade_out(0,2);
}

void SceneOptions::render(float camera_x, float camera_y)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->render(camera_x, camera_y);
	}

	//soundAnimation->render(3, 100,100);
	soundAnimation->animate(150,100,100);
}

int SceneOptions::update(int detective)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->update(detective);
	}

	soundAnimation->update(detective, true, 0, false);

	return 0;
}

void SceneOptions::Exit()
{
	this->clean_game_objects();
}

