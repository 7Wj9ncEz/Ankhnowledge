/*
 * GameManager.cpp
 *
 *  Class manages the game overall be it scenes, technology, splash and others
 *
 */

#include "GameManager.h"

#include <iostream>
#include <sstream>
#include <assert.h>
using namespace std;

FadeScreen * GameManager::fade_screen = 0;
Scene * GameManager::current_scene = 0;
string SDLBase::resourcesPath = getenv("HOME");

/**
 * Class Constructor
 * Before loading an image itś necessary to initialize the SDL
 * Once the Sprite constructor uses the function SDLBase::loadImage(char *file)
 * That uses the functions SDL_DisplayFormar and SDL_DisplayFormaAlpha
**/
GameManager::GameManager() {
	
	// Init-Function Logs
    log("Animation destructor called", GameManager);
	
	// Gets the needed resource's path
	SDLBase::resourcesPath = SDLBase::resourcesPath + "/../../usr/local/Ankhnowledge/resources/";
	
	// Tests
    TEST_CASE("Testing GameManager Constructor", "[GameManager]") {
        REQUIRE(SDLBase::resourcesPath == SDLBase::resourcesPath + "/../../usr/local/Ankhnowledge/resources/");
    }
	
	SDLBase::initializeSDL();
	initResources();
	
	// Post-Function Logs
    log("GameManager called initializeSDL()", GameManager);
    log("GameManager called initResources()", GameManager);
    log("GameManager has ended", GameManager);

}

/**
 * Class Destructor
 **/
GameManager::~GameManager() {
    
    // Init-Function Logs
    log("GameManager Destructor called", GameManager);
    
    // Deleting all splashes
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
	
	// Post-Function Logs
    log("GameManager Destructor has ended", GameManager);
}

/**
 * Function that initializes the objects (resources) in the game
**/
void GameManager::initResources() {
    
    // Init-Function Logs
    log("Init Resources (GameManager) called", GameManager);

    // Creating all new splashes and message boxes
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

	fade_screen = new FadeScreen(SDLBase::getScreen()->w, SDLBase::getScreen()->h);
	fade_screen->fade_out(0,2);
	current_scene = splashLogo;
	current_scene->Enter();
	
	// Mid-Function Logs
    log("fade_screen initialized", GameManager);
    log("initResources -> fade_screen" + fade_screen, GameManager);
    log("initResources -> current_scene" + current_scene , GameManager);
    log("initResources -> current_scene called Enter()", GameManager);

    // Initializing network connection also input and audio managers
	Network::init();
	input = InputManager::getInstance();
	audio = AudioHandler::getInstance();
	
	// Mid-Function Logs
    log("initResources called Network::init()", GameManager);
    log("initResources -> input" + InputManager::getInstance(), GameManager);
    log("initResources -> audio" + AudioHandler::getInstance(), GameManager);
	
	// Default values
	dt = 0;
	frame_start = 0;
	frame_end = 0;
	quit = false;
	render_quit_box = false;
	esc_pressed = false;
	
	// Mid-Function Logs
    log("initResources -> dt" + dt, GameManager);
    log("initResources -> frame_start" + frame_start, GameManager);
    log("initResources -> frame_end" + frame_end, GameManager);
    log("initResources -> quit" + quit, GameManager);
    log("initResources -> render_quit_box" + render_quit_box, GameManager);
    log("initResources -> esc_pressed" + esc_pressed, GameManager);
	
	// Post-Function Logs
    log("initResouces() has ended", GameManager);
}

/**
 * Function that makes the loop in the game
**/
void GameManager::processEvents() {
    
    // Init-Function Logs
    log("Process Events (GameManager) called", GameManager);

	// Searches an event
	input->Update();
	if (input->QuitGame()) {
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent( &quit );
		
	    // Mid-Function Logs
        log("quit SDL_Event", GameManager);
        log("processEvents -> quit.type" + quit.type, GameManager);
        log("processEvents has called SDL_PushEvent ( &quit )", GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_ESCAPE) && esc_pressed == false) {
		// If 'ESC' is pressed, leaved the program
		render_quit_box = true;
		esc_pressed = true;
		
		// Mid-Function Logs
        log("processEvents -> render_quit_box" + render_quit_box, GameManager);
        log("processEvents -> esc_pressed" + esc_pressed, GameManager);
	}

	else {
		// Nothing to do
	}

	//Skip
	if((input->is_key_down(SDLK_SPACE))
	&& ((current_scene->get_scene_name() == "SceneLogo")
	|| (current_scene->get_scene_name() == "SceneTechnology")
	|| (current_scene->get_scene_name() == "SceneThirdParty")
	|| (current_scene->get_scene_name() == "SceneLegal"))) {
	    current_scene = splashMainMenu;
	    current_scene->Enter();
	    
	    // Mid-Function Logs
        log("processEvents -> current_scene" + current_scene, GameManager);
        log("processEvents -> current_scene has called Enter()", GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_UP)) {
		camera_speed_y -= SCROLL;
		
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_DOWN)) {
		camera_speed_y += SCROLL;
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_LEFT)) {
		camera_speed_x -= SCROLL;
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_RIGHT)) {
		camera_speed_x += SCROLL;
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_UP)) {
		camera_speed_y += SCROLL;
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_DOWN)) {
		camera_speed_y -= SCROLL;
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_LEFT)) {
		camera_speed_x += SCROLL;
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_RIGHT)) {
		camera_speed_x -= SCROLL;
	}

	else {
		// Nothing to do
	}
	
	// Post-Function Logs
    log("processEvents() has ended", GameManager);
}

/**
 * Responsible for updating the GameManager
**/
void GameManager::update(int dt) {

	// Asserts
	assert(dt >= 0);

	if (quit) {
		Network::finish();
		SDL_Event quit;
 		quit.type = SDL_QUIT;
    		SDL_PushEvent(&quit);
	}

	else {
		// Nothing to do
	}

	if (render_quit_box) {
		mb->update(dt);
		if (mb->confirm_pressed()) {
			quit = true;
		}

		else if (mb->cancelPressed()) {
			render_quit_box = false;
			esc_pressed = false;
			mb->deactivateCancel();
		}

		else {
			// Nothing to do
		}
	}

	else {
		current_scene->update(dt);
		fade_screen->update(dt);
		audio->update();
		camera_x1 += camera_speed_x;
		camera_y1 += camera_speed_y;
	}
}

/**
 * Responsible for rendering the GameManager around a specific area in the camera_y1
 *
 * Parameters:
 * "camera_x & camera_y" are the camera axis that will be rendered
**/
void GameManager::render(float camera_x, float camera_y){

	// Asserts
	assert(camera_x >= 0);
	assert(camera_y >= 0);

	current_scene->render(0,0);

	if (render_quit_box) {
		mb->render(0,0);
	}

	else {
		// Nothing to do
	}
	fade_screen->render(0,0);
}

/**
 * Responsible for running the GameManager
**/
void GameManager::run() {

	while(!SDL_QuitRequested()) {

		frame_start = SDL_GetTicks();
		dt = frame_start - frame_end;

		if (current_scene->should_change_scene() && fade_screen->isFaded()) {
			current_scene->Exit();
			current_scene = current_scene->getNextScene();
			current_scene->Enter();
		}

		else {
			// Nothing to do
		}

		if (dt >= 1000/30) {

			// Captures the input
			processEvents();

			// Updates
			update(dt);

			// Renders the objects
			render(camera_x1, camera_y1);

			// Updates the screen
			SDLBase::updateScreen();
			frame_end = SDL_GetTicks();

		}

		else {
			SDL_Delay(1000/30 -dt);
		}

		this->current_scene->clean_destroyed_game_objects();
	}
}
