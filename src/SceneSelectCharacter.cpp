/*
 * SceneSelectCharacter.cpp
 *
 * Scene responsible for the character selection
 */

#include "SceneSelectCharacter.h"
#include <string>
SceneSelectCharacter::SceneSelectCharacter(string scene_name) : Scene (scene_name) {

}

SceneSelectCharacter::~SceneSelectCharacter() {
}

/**
 * Changes the game scene to the chacter selection
**/
void SceneSelectCharacter::Enter() {
	AudioHandler * audio = AudioHandler::getInstance();
 	audio->stopMusic();
   	audio->set_music("tela_de_selecao_de_mapas.ogg");
 	audio->play_music(-1);

	cc = new SelectCharacterController();
	this->addGameObject(cc);
	GameManager::fade_screen->fade_out(0,2);
}

/**
 * Cleans all the game_objects created by the class "SceneSelectCharacter"
**/
void SceneSelectCharacter::Exit() {
	this->clean_game_objects();
}
