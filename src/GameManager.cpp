
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

	this->splashLogo->addScenes(splashTechnology);
	this->splashTechnology->addScenes(splashThirdParty);
	this->splashThirdParty->addScenes(splashLegal);
	this->splashLegal->addScenes(splashMainMenu);
	this->splashMainMenu->addScenes(splashPhaseOne);
	this->splashMainMenu->addScenes(splashCredits);
	this->splashMainMenu->addScenes(splashOptions);
	this->splashMainMenu->addScenes(splashSelectCharacter);
	this->splashOptions->addScenes(splashMainMenu);
	this->splashCredits->addScenes(splashMainMenu);
	this->splashPhaseOne->addScenes(splashMainMenu);
	this->splashPhaseOne->addScenes(splashSelectCharacter);
	this->splashPhaseTwo->addScenes(splashMainMenu);
	this->splashPhaseTwo->addScenes(splashSelectCharacter);
	this->splashPhaseThree->addScenes(splashMainMenu);
	this->splashPhaseThree->addScenes(splashSelectCharacter);
	this->splashPhaseFour->addScenes(splashMainMenu);
	this->splashPhaseFour->addScenes(splashSelectCharacter);
	this->splashPhaseFive->addScenes(splashMainMenu);
	this->splashPhaseFive->addScenes(splashSelectCharacter);
	this->splashSelectMap->addScenes(splashPhaseOne);
	this->splashSelectMap->addScenes(splashPhaseTwo);
	this->splashSelectMap->addScenes(splashPhaseThree);
	this->splashSelectMap->addScenes(splashPhaseFour);
	this->splashSelectMap->addScenes(splashPhaseFive);
	this->splashSelectMap->addScenes(splashMainMenu);
	this->splashSelectCharacter->addScenes(splashSelectMap);
	this->splashSelectCharacter->addScenes(splashMainMenu);

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
	if(input->QuitGame()){
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent( &quit );
	}

	if(input->isKeyDown(SDLK_ESCAPE) && escPressed == false){	
		// se a tecla ESC foi pressionada, sair do programa
		renderQuitBox = true;
		escPressed = true;
	}


	//Skip

	if((input->isKeyDown(SDLK_SPACE)) 
	&& ((currentScene->getSceneName() == "SceneLogo")
	|| (currentScene->getSceneName() == "SceneTechnology")
	|| (currentScene->getSceneName() == "SceneThirdParty")
	|| (currentScene->getSceneName() == "SceneLegal"))){
	    currentScene = splashMainMenu;
	    currentScene->Enter();
	}

	if( input->isKeyDown(SDLK_UP) )
		camera_speed_y -= SCROLL;
	if( input->isKeyDown(SDLK_DOWN) )
		camera_speed_y += SCROLL;
	if( input->isKeyDown(SDLK_LEFT) )
		camera_speed_x -= SCROLL;
	if( input->isKeyDown(SDLK_RIGHT) )
		camera_speed_x += SCROLL;

	if( input->isKeyUp(SDLK_UP) )
		camera_speed_y += SCROLL;
	if( input->isKeyUp(SDLK_DOWN) )
		camera_speed_y -= SCROLL;
	if( input->isKeyUp(SDLK_LEFT) )
		camera_speed_x += SCROLL;
	if( input->isKeyUp(SDLK_RIGHT) )
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
	
	if(renderQuitBox)
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
	if(renderQuitBox)		
		mb->render(0,0);
	fadeScreen->render(0,0);
}

void GameManager::run(){

	while(!SDL_QuitRequested()){

		frame_start = SDL_GetTicks();
		dt = frame_start - frameEnd;

		if(currentScene->shouldChangeScene() && fadeScreen->isFaded())
		{
			currentScene->Exit();
			currentScene = currentScene->getNextScene();
			currentScene->Enter();
		}



		if(dt >= 1000/30){
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

		this->currentScene->cleanDestroyedGameObjects();
	}
}
