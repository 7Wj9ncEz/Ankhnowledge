/*
 * SceneSelectMap.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#include "SceneSelectMap.h"

SceneSelectMap::SceneSelectMap(string scene_name) : Scene (scene_name) {

}

SceneSelectMap::~SceneSelectMap() {
}

void SceneSelectMap::Enter()
{
	cc = new SelectMapController();
		this->addGameObject(cc);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneSelectMap::Exit()
{
	this->clean_game_objects();
}

