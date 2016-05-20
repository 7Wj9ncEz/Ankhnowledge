/*
 * SceneGameOver.cpp
 *
 * Class that is used to show the user the "Game Over" screen
 *
 */

#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(string scene_name) : Scene (scene_name)  {
	// TODO Auto-generated constructor stub
}

SceneGameOver::~SceneGameOver() {
	// TODO Auto-generated destructor stub
}

/**
 * Creates a new sprite that will show that the player lost the Game
 * Also shows the "game over scene"
**/
void SceneGameOver::Enter() {
	this->splashSprite = new Sprite(SDLBase::resourcesPath + "lost.png");
	string nextScene = "SceneGameOver" ;
	SplashScreen * splashScreen =  new SplashScreen(splashSprite,nextScene);
	this->addGameObject(splashScreen);
	GameManager::fade_screen->fade_out(0,2);
}

/**
 * Cleans all the game objects of the GameOver scene
**/
void SceneGameOver::Exit() {
	this->clean_game_objects();
}
