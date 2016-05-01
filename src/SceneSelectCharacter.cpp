/*
 * SceneSelectCharacter.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#include "SceneSelectCharacter.h"
#include <string>
SceneSelectCharacter::SceneSelectCharacter(string scene_name) : Scene (scene_name) {

}

SceneSelectCharacter::~SceneSelectCharacter() {
}

void SceneSelectCharacter::Enter()
{
	AudioHandler * audio = AudioHandler::getInstance();
 	audio->stopMusic();
   	audio->set_music("tela_de_selecao_de_mapas.ogg");
 	audio->play_music(-1);

	cc = new SelectCharacterController();
	this->addGameObject(cc);
	GameManager::fadeScreen->fade_out(0,2);
}

void SceneSelectCharacter::Exit()
{
	this->clean_game_objects();
}

