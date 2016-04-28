/*
 * SceneOptions.cpp
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#include <iostream>
#include "SceneOptions.h"

SceneOptions::SceneOptions(string sceneName) : Scene (sceneName)  {
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

	GameManager::fadeScreen->fadeOut(0,2);
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

int SceneOptions::update(int dt)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->update(dt);
	}

	soundAnimation->update(dt, true, 0, false);

	return 0;
}

void SceneOptions::Exit()
{
	this->cleanGameObjects();
}

