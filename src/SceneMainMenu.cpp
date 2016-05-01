/*
 * SceneMainMenu.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#include "SceneMainMenu.h"

SceneMainMenu::SceneMainMenu(string scene_name) : Scene (scene_name) {

}

SceneMainMenu::~SceneMainMenu() {
}

void SceneMainMenu::Enter()
{
	AudioHandler * audio = AudioHandler::getInstance();
 	audio->stopMusic();
   	audio->set_music("tema.ogg");
 	audio->play_music(-1);

	buttons = new MainMenuButHandler();
	this->addGameObject(buttons);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneMainMenu::Exit()
{
	this->clean_game_objects();
}

