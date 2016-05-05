
#include "GameManager.h"

#include <iostream>
#include <sstream>
using namespace std;

FadeScreen * GameManager::fadeScreen = 0;
Scene * GameManager::currentScene = 0;
string SDLBase::resourcesPath = getenv("HOME");

/*
 * Construtor da Classe
 * Antes de carregar a imagem e necessario inicialiar o SDL, uma vez que o construtor
 * do Sprite faz uso do metodo SDLBase::loadImage(char * arquivo), que faz uso das
 * funcoes SDL_DisplayFormat e SDL_DisplayFormaAlpha. Funcoes estas que precisam
 */
GameManager::GameManager() {
	SDLBase::resourcesPath = SDLBase::resourcesPath + "/../../usr/local/Ankhnowledge/resources/";
	SDLBase::initializeSDL();
	initResources();

}

/*
 * Destrutor da Clase
 */
GameManager::~GameManager() {
	delete splashLogo;
	delete splashTechnology;
	delete splashThirdParty;
	delete splashLegal;
	delete splashMainMenu;
	delete splashPhaseOne;
	delete splashPhaseTwo;
	delete splashPhaseThree;
	delete splashPhaseFour;
	delete splashPhaseFive;
	delete splashSelectMap;
	delete splashSelectCharacter;
}

//Metodo que inicializa os objetos (recursos) do jogo
void GameManager::initResources(){

	this->splashLogo = new SceneLogo("SceneLogo");
	this->splashTechnology = new SceneTechnology("SceneTechnology");
	this->splashThirdParty = new SceneThirdParty("SceneThirdParty");
	this->splashLegal = new SceneLegal("SceneLegal");
	this->splashMainMenu = new SceneMainMenu("SceneMainMenu");
	this->splashPhaseOne = new ScenePhaseOne("ScenePhaseOne");
	this->splashPhaseTwo = new ScenePhaseTwo("ScenePhaseTwo");
	this->splashPhaseThree = new ScenePhaseThree("ScenePhaseThree");
	this->splashPhaseFour = new ScenePhaseFour("ScenePhaseFour");
	this->splashPhaseFive = new ScenePhaseFive("ScenePhaseFive");
	this->splashGameOver = new SceneGameOver("SceneGameOver");
	this->splashCredits = new SceneCredits("SceneCredits");
	this->splashOptions = new SceneOptions("SceneOptions");
	this->splashSelectMap = new SceneSelectMap("SceneSelectMap");
	this->splashSelectCharacter = new SceneSelectCharacter("SceneSelectCharacter");
	this->box_spr = new Sprite(SDLBase::resourcesPath + "leavethegamebox.png");
	this->mb = new MessageBox(box_spr, "yes","no",250,200);	

	this->splashLogo->add_scenes(splashTechnology);
	this->splashTechnology->add_scenes(splashThirdParty);
	this->splashThirdParty->add_scenes(splashLegal);
	this->splashLegal->add_scenes(splashMainMenu);
	this->splashMainMenu->add_scenes(splashPhaseOne);
	this->splashMainMenu->add_scenes(splashCredits);
	this->splashMainMenu->add_scenes(splashOptions);
	this->splashMainMenu->add_scenes(splashSelectCharacter);
	this->splashOptions->add_scenes(splashMainMenu);
	this->splashCredits->add_scenes(splashMainMenu);
	this->splashPhaseOne->add_scenes(splashMainMenu);
	this->splashPhaseOne->add_scenes(splashSelectCharacter);
	this->splashPhaseTwo->add_scenes(splashMainMenu);
	this->splashPhaseTwo->add_scenes(splashSelectCharacter);
	this->splashPhaseThree->add_scenes(splashMainMenu);
	this->splashPhaseThree->add_scenes(splashSelectCharacter);
	this->splashPhaseFour->add_scenes(splashMainMenu);
	this->splashPhaseFour->add_scenes(splashSelectCharacter);
	this->splashPhaseFive->add_scenes(splashMainMenu);
	this->splashPhaseFive->add_scenes(splashSelectCharacter);
	this->splashSelectMap->add_scenes(splashPhaseOne);
	this->splashSelectMap->add_scenes(splashPhaseTwo);
	this->splashSelectMap->add_scenes(splashPhaseThree);
	this->splashSelectMap->add_scenes(splashPhaseFour);
	this->splashSelectMap->add_scenes(splashPhaseFive);
	this->splashSelectMap->add_scenes(splashMainMenu);
	this->splashSelectCharacter->add_scenes(splashSelectMap);
	this->splashSelectCharacter->add_scenes(splashMainMenu);

	fadeScreen = new FadeScreen(SDLBase::getScreen()->w, SDLBase::getScreen()->h);
	fadeScreen->fade_out(0,2);
	currentScene = splashLogo;
	currentScene->Enter();

	Network::init();
	input = InputManager::getInstance();
	audio = AudioHandler::getInstance();
	dt = 0;
	frame_start = 0;
	frameEnd = 0;
	quit = false;
	renderQuitBox = false;
	escPressed = false;
}


// Metodo que realiza o game loop

void GameManager::processEvents(){
	// procura um event
	input->Update();
	if (input->QuitGame()){
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent( &quit );
	}

	if (input->is_key_down(SDLK_ESCAPE) && escPressed == false){	
		// se a tecla ESC foi pressionada, sair do programa
		renderQuitBox = true;
		escPressed = true;
	}


	//Skip

	if((input->is_key_down(SDLK_SPACE)) 
	&& ((currentScene->get_scene_name() == "SceneLogo")
	|| (currentScene->get_scene_name() == "SceneTechnology")
	|| (currentScene->get_scene_name() == "SceneThirdParty")
	|| (currentScene->get_scene_name() == "SceneLegal"))){
	    currentScene = splashMainMenu;
	    currentScene->Enter();
	}

	if( input->is_key_down(SDLK_UP) )
		camera_speed_y -= SCROLL;
	if( input->is_key_down(SDLK_DOWN) )
		camera_speed_y += SCROLL;
	if( input->is_key_down(SDLK_LEFT) )
		camera_speed_x -= SCROLL;
	if( input->is_key_down(SDLK_RIGHT) )
		camera_speed_x += SCROLL;

	if( input->is_key_up(SDLK_UP) )
		camera_speed_y += SCROLL;
	if( input->is_key_up(SDLK_DOWN) )
		camera_speed_y -= SCROLL;
	if( input->is_key_up(SDLK_LEFT) )
		camera_speed_x += SCROLL;
	if( input->is_key_up(SDLK_RIGHT) )
		camera_speed_x -= SCROLL;

}

void GameManager::update(int dt){
	if (quit)
	{
		Network::finish();
		SDL_Event quit;
 		quit.type = SDL_QUIT;
    		SDL_PushEvent( &quit );
	}
	
	if (renderQuitBox)
	{
		mb->update(dt);
		if (mb->confirmPressed())
		{
			quit = true;
		}
		else if (mb->cancelPressed())
		{
			renderQuitBox = false;
			escPressed = false;
			mb->deactivateCancel();
		}
	}
	else 
	{
		currentScene->update(dt);
		fadeScreen->update(dt);
		audio->update();
		cameraX1 += camera_speed_x;
		cameraY1 += camera_speed_y;
	}
}

void GameManager::render(float camera_x, float camera_y){
	currentScene->render(0,0);
	if (renderQuitBox)		
		mb->render(0,0);
	fadeScreen->render(0,0);
}

void GameManager::run(){

	while(!SDL_QuitRequested()){

		frame_start = SDL_GetTicks();
		dt = frame_start - frameEnd;

		if (currentScene->should_change_scene() && fadeScreen->isFaded())
		{
			currentScene->Exit();
			currentScene = currentScene->getNextScene();
			currentScene->Enter();
		}



		if (dt >= 1000/30){
			/* Captura de Input*/
			processEvents();

			/*Realizar Update*/
			update(dt);

			/*Renderizar os objetos*/
			render(cameraX1, cameraY1);

			/*Atualizar a tela*/
			SDLBase::updateScreen();
			frameEnd = SDL_GetTicks();

		}else{
			SDL_Delay(1000/30 -dt);
		}

		this->currentScene->clean_destroyed_game_objects();
	}
}
