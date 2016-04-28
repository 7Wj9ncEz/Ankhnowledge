

#include "Scene.h"
#include <iostream>
#include <stdio.h>

Scene::Scene(string sceneName) {
	this->sceneName = sceneName;
	this->sChangeScene = false;
	this->nextScene = 0;
}

Scene::~Scene() {
	gameObjects.clear();
}

void Scene::addScenes(Scene *scene)
{
	this->scenes.push_back(scene);
}

int Scene::changeScene(string sceneName)
{

	for (list<Scene *>::iterator it = scenes.begin(); it != scenes.end(); it++)
	{
		if((*(*it)->getName()) == sceneName)
		{
			nextScene = (*it);
			this->sChangeScene = true;
			return SUCCESS;
		}
	}
	return SCENE_DOESNT_EXIST;
}

string * Scene::getName()
{
	return &(this->sceneName);
}

bool Scene::shouldChangeScene()
{
	return this->sChangeScene;
}

list<GameObject *> Scene::getAllGameObject()
{
	return (this->gameObjects);
}

void Scene::addGameObject(GameObject * gameObject)
{
	this->gameObjects.push_back(gameObject);
}

void Scene::cleanGameObjects()
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		delete (*it);
	}
	gameObjects.clear();
	sChangeScene = false;
}

int Scene::update(int dt)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->update(dt);
	}
	return 0;
}

void Scene::render(float camera_x, float camera_y)
{
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->render(camera_x, camera_y);
	}
}

Scene * Scene::getNextScene()
{
	return this->nextScene;
}

string Scene::getSceneName(){
	return this->sceneName;
}

void Scene::destroyGameObject(GameObject * gameObject)
{
	this->garbage.push_back(gameObject);

	//delete gameObject;
}

void Scene::cleanDestroyedGameObjects()
{
	if(!this->garbage.empty())
	{

	for(unsigned int i = 0; i < this->garbage.size(); i++)
	{
		gameObjects.remove(this->garbage.at(i));
		delete garbage.at(i);
	}

	this->garbage.clear();
	}
}



