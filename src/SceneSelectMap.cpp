/*
 * SceneSelectMap.cpp
 *
 * Scene responsible for the map selection
 */

#include "SceneSelectMap.h"

SceneSelectMap::SceneSelectMap(string scene_name) : Scene (scene_name) {

}

SceneSelectMap::~SceneSelectMap() {
}

/**
 * Changes the game scene to the map selection
**/
void SceneSelectMap::Enter() {
	cc = new SelectMapController();
		this->addGameObject(cc);
	GameManager::fade_screen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "SceneSelectMap"
**/
void SceneSelectMap::Exit() {
	this->clean_game_objects();
}
