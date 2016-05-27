/*
 * File:   scene.cpp
 *
 * Responsible for creating/managing the scenes in the game
 */

#include "Scene.h"
#include <iostream>
#include <stdio.h>
#include <assert.h>

Scene::Scene(string scene_name) {
	this->scene_name = scene_name;
	this->sChangeScene = false;
	this->nextScene = 0;
}

Scene::~Scene() {
	gameObjects.clear();
}

/**
 * Receives a scene object and add it into the scenes queue
 *
 * Parameters:
 * "*scene" is a Scene object (pointer) that will be added by the function in
 * the Scene's queue
**/
void Scene::add_scenes(Scene *scene) {

	// Asserts
    assert(scene != NULL);

	this->scenes.push_back(scene);
}

/**
 * Responsible for changing the scene for another that is in the Scene queue
 *
 * Parameters:
 * "scene_name" is a string with the name of the Scene that will be changed
**/
int Scene::change_scene(string scene_name) {

	for (list<Scene *>::iterator it = scenes.begin(); it != scenes.end(); it++) {
		if ((*(*it)->getName()) == scene_name) {
			nextScene = (*it);
			this->sChangeScene = true;
			return SUCCESS;
		}

		else {
			// Nothing to do
		}
	}

	return SCENE_DOESNT_EXIST;
}

/**
 * Regular getter that returns a scene's name
**/
string * Scene::getName() {
	return &(this->scene_name);
}

/**
 * Regular getter that shows a boolean value if it's time to change the scene
**/
bool Scene::should_change_scene() {
	return this->sChangeScene;
}

/**
 * regular getter that returns all Scene's gameObjects.
**/
list<GameObject *> Scene::getAllGameObject() {
	return (this->gameObjects);
}

/**
 * Adds a gameObject into the scene
 *
 * Parameters:
 * "gameObject" is an object type GameObject that will be added into the scene
**/
void Scene::addGameObject(GameObject * gameObject) {

	// Asserts
    assert(gameObject != NULL);

	this->gameObjects.push_back(gameObject);
}

/**
 * Clean all gameObject's that are in the Scene
**/
void Scene::clean_game_objects() {
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		delete (*it);
	}
	gameObjects.clear();
	sChangeScene = false;
}

/**
 * For every change into the Scene this function must be called to update it
**/
int Scene::update(int dt) {
	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		(*it)->update(dt);
	}
	return 0;
}

/**
 * Renders the scene according to the position x,y given
 *
 * Parameters:
 * "camera_x & camera_y" positions of each axis of the camera to render the Scene
**/
void Scene::render(float camera_x, float camera_y) {

	// Asserts
    assert(camera_x >= 0);
    assert(camera_y >= 0);

	for (list<GameObject *>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++) {
		(*it)->render(camera_x, camera_y);
	}
}

/**
 * Regular getter that returns which will be the next scene
**/
Scene * Scene::getNextScene() {
	return this->nextScene;
}

/**
 * Regular getter that also shows the scene's name
**/
string Scene::get_scene_name() {
	return this->scene_name;
}

/**
 * Cleans a specific GameObject throwing it into the garbage queue
 *
 * Parameters:
 * "gameObject" an object of GameObject that will be "thrown" in the garbage
**/
void Scene::destroy_game_object(GameObject * gameObject) {

	// Asserts
    assert(gameObject != NULL);

	this->garbage.push_back(gameObject);

	//delete gameObject;
}

/**
 * Clean the garbage collector filled with gameObjects
**/
void Scene::clean_destroyed_game_objects() {
	if (!this->garbage.empty()) {
		for(unsigned int i = 0; i < this->garbage.size(); i++)
		{
			gameObjects.remove(this->garbage.at(i));
			delete garbage.at(i);
		}

		this->garbage.clear();
	}

	else {
		// Nothing to do
	}
}
