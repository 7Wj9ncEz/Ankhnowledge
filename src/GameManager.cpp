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
#include "log.h"
#include "catch.hpp"

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
	this->message_box = new MessageBox(box_spr, "yes","no",250,200);

	// Tests
    TEST_CASE("Testing initResouces (GameManager) [1-3]", "[GameManager]") {
		REQUIRE(this->splashLogo != NULL);
		REQUIRE(this->splashTechnology != NULL);
		REQUIRE(this->splashThirdParty != NULL);
		REQUIRE(this->splashLegal != NULL);
		REQUIRE(this->splashMainMenu != NULL);
		REQUIRE(this->splashPhaseOne != NULL);
		REQUIRE(this->splashPhaseTwo != NULL);
		REQUIRE(this->splashPhaseThree != NULL);
		REQUIRE(this->splashPhaseFour != NULL);
		REQUIRE(this->splashPhaseFive != NULL);
		REQUIRE(this->splashGameOver != NULL);
		REQUIRE(this->splashCredits != NULL);
		REQUIRE(this->splashOptions != NULL);
		REQUIRE(this->splashSelectMap != NULL);
		REQUIRE(this->splashSelectCharacter != NULL);
		REQUIRE(this->box_spr != NULL);
		REQUIRE(this->message_box != NULL);
    }

	// Mid-Function Logs
    log("initResouces -> splashLogo initialized = " + splashLogo, GameManager);
	log("initResouces -> splashTechnology initialized = " + splashTechnology, GameManager);
	log("initResouces -> splashThirdParty initialized = " + splashThirdParty, GameManager);
	log("initResouces -> splashLegal initialized = " + splashLegal, GameManager);
	log("initResouces -> splashMainMenu initialized = " + splashMainMenu, GameManager);
	log("initResouces -> splashPhaseOne initialized = " + splashPhaseOne, GameManager);
	log("initResouces -> splashPhaseTwo initialized = " + splashPhaseTwo, GameManager);
	log("initResouces -> splashPhaseThree initialized = " + splashPhaseThree, GameManager);
	log("initResouces -> splashPhaseFour initialized = " + splashPhaseFour, GameManager);
	log("initResouces -> splashPhaseFive initialized = " + splashPhaseFive, GameManager);
	log("initResouces -> splashGameOver initialized = " + splashGameOver, GameManager);
	log("initResouces -> splashCredits initialized = " + splashCredits, GameManager);
	log("initResouces -> splashCredits initialized = " + splashCredits, GameManager);
	log("initResouces -> splashOptions initialized = " + splashOptions, GameManager);
	log("initResouces -> splashSelectMap initialized = " + splashSelectMap, GameManager);
	log("initResouces -> splashSelectCharacter initialized = " + splashSelectCharacter, GameManager);
	log("initResouces -> box_spr initialized = " + box_spr, GameManager);
	log("initResouces -> message_box initialized = " + message_box, GameManager);

	// Adding scenes into the splashes
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

	// Mid-Function Logs
	log("initResouces -> scene added into splashLogo = " + splashTechnology, GameManager);
	log("initResouces -> scene added into splashTechnology = " + splashThirdParty, GameManager);
	log("initResouces -> scene added into splashThirdParty = " + splashLegal, GameManager);
	log("initResouces -> scene added into splashLegal = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashMainMenu = " + splashPhaseOne, GameManager);
	log("initResouces -> scene added into splashMainMenu = " + splashCredits, GameManager);
	log("initResouces -> scene added into splashMainMenu = " + splashOptions, GameManager);
	log("initResouces -> scene added into splashOptions = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashCredits = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashPhaseOne = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashPhaseOne = " + splashSelectCharacter, GameManager);
	log("initResouces -> scene added into splashPhaseTwo = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashPhaseTwo = " + splashSelectCharacter, GameManager);
	log("initResouces -> scene added into splashPhaseThree = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashPhaseThree = " + splashSelectCharacter, GameManager);
	log("initResouces -> scene added into splashPhaseFour = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashPhaseFour = " + splashSelectCharacter, GameManager);
	log("initResouces -> scene added into splashPhaseFive = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashPhaseFive = " + splashSelectCharacter, GameManager);
	log("initResouces -> scene added into splashSelectMap = " + splashPhaseOne, GameManager);
	log("initResouces -> scene added into splashSelectMap = " + splashPhaseTwo, GameManager);
	log("initResouces -> scene added into splashSelectMap = " + splashPhaseThree, GameManager);
	log("initResouces -> scene added into splashSelectMap = " + splashPhaseFour, GameManager);
	log("initResouces -> scene added into splashSelectMap = " + splashPhaseFive, GameManager);
	log("initResouces -> scene added into splashSelectMap = " + splashMainMenu, GameManager);
	log("initResouces -> scene added into splashSelectCharacter = " + splashSelectMap, GameManager);
	log("initResouces -> scene added into splashSelectCharacter = " + splashMainMenu, GameManager);

	fade_screen = new FadeScreen(SDLBase::getScreen()->w, SDLBase::getScreen()->h);
	fade_screen->fade_out(0,2);
	current_scene = splashLogo;
	current_scene->Enter();

	// Tests
    TEST_CASE("Testing initResouces (GameManager) [2-3]", "[GameManager]") {
		REQUIRE(fade_screen != NULL);
		REQUIRE(current_scene == splashLogo);
	}

	// Mid-Function Logs
    log("initResouces -> fade_screen initialized = " + fade_screen, GameManager);
    log("initResources -> fade_screen = " + fade_screen, GameManager);
    log("initResources -> current_scene = " + current_scene , GameManager);
    log("initResources -> current_scene has called Enter()", GameManager);

    // Initializing network connection also input and audio managers
	Network::init();
	input = InputManager::getInstance();
	audio = AudioHandler::getInstance();

	// Mid-Function Logs
    log("initResources called Network::init()", GameManager);
    log("initResources -> input = " + InputManager::getInstance(), GameManager);
    log("initResources -> audio = " + AudioHandler::getInstance(), GameManager);

	// Default values
	dt = 0;
	frame_start = 0;
	frame_end = 0;
	quit = false;
	render_quit_box = false;
	esc_pressed = false;

	// Tests
    TEST_CASE("Testing initResouces (GameManager) [3-3]", "[GameManager]") {
		REQUIRE(dt == 0);
		REQUIRE(frame_start == 0);
		REQUIRE(frame_end) == 0);
		REQUIRE(quit == false);
		REQUIRE(render_quit_box == false);
		REQUIRE(esc_pressed == false);
	}

	// Mid-Function Logs
    log("initResources -> dt = " + dt, GameManager);
    log("initResources -> frame_start = " + frame_start, GameManager);
    log("initResources -> frame_end = " + frame_end, GameManager);
    log("initResources -> quit = " + quit, GameManager);
    log("initResources -> render_quit_box = " + render_quit_box, GameManager);
    log("initResources -> esc_pressed = " + esc_pressed, GameManager);

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
	// Mid-Function Logs
	log("processEvents -> input has called Update()", GameManager);

	if (input->QuitGame()) {
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent( &quit );

	    // Mid-Function Logs
        log("quit SDL_Event", GameManager);
        log("processEvents -> quit.type = " + quit.type, GameManager);
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
        log("processEvents -> render_quit_box = " + render_quit_box, GameManager);
        log("processEvents -> esc_pressed = " + esc_pressed, GameManager);
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
        log("processEvents -> current_scene = " + current_scene, GameManager);
        log("processEvents -> current_scene has called Enter()", GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_UP)) {
		camera_speed_y -= SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_y = " + camera_speed_y, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_DOWN)) {
		camera_speed_y += SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_y = " + camera_speed_y, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_LEFT)) {
		camera_speed_x -= SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_x = " + camera_speed_x, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_down(SDLK_RIGHT)) {
		camera_speed_x += SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_x = " + camera_speed_x, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_UP)) {
		camera_speed_y += SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_y = " + camera_speed_y, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_DOWN)) {
		camera_speed_y -= SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_y = " + camera_speed_y, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_LEFT)) {
		camera_speed_x += SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_x = " + camera_speed_x, GameManager);
	}

	else {
		// Nothing to do
	}

	if (input->is_key_up(SDLK_RIGHT)) {
		camera_speed_x -= SCROLL;

		// Mid-Function Logs
        log("processEvents -> camera_speed_x = " + camera_speed_x, GameManager);
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

	// Init-Function Logs
    log("Update GameManager has been called", GameManager);
    log("update -> dt = " + dt, GameManager);

	if (quit) {
		Network::finish();
		SDL_Event quit;
 		quit.type = SDL_QUIT;
    	SDL_PushEvent(&quit);

		// Mid-Function Logs
		log("update called Network::finish()", GameManager);
		log("update called SDL_event quit", GameManager);
		log("update called SDL_PushEvent(&quit)", GameManager);
	}

	else {
		// Nothing to do
	}

	if (render_quit_box) {
		message_box->update(dt);
		if (message_box->confirm_pressed()) {
			quit = true;

			// Mid-Function Logs
			log("update -> quit = " + quit, GameManager);
		}

		else if (message_box->cancelPressed()) {
			render_quit_box = false;
			esc_pressed = false;
			message_box->deactivateCancel();

			// Mid-Function Logs
			log("update -> render_quit_box = " + render_quit_box, GameManager);
			log("update -> esc_pressed = " + esc_pressed, GameManager);
			log("update -> message_box has called deactivateCancel()", GameManager);
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

		// Mid-Function Logs
		log("update -> current_scene has called update(dt)", GameManager);
		log("update -> fade_screen has called update(dt)", GameManager);
		log("update -> audio has called update()", GameManager);
		log("update -> camera_x1 = " + camera_x1, GameManager);
		log("update -> camera_y1 = " + camera_y1, GameManager);
	}

	// Post-Function Logs
    log("update() has ended", GameManager);
}

/**
 * Responsible for rendering the GameManager around a specific area in the camera_y1
 *
 * Parameters:
 * "camera_x & camera_y" are the camera axis that will be rendered
**/
void GameManager::render(float camera_x, float camera_y) {

	// Asserts
	assert(camera_x >= 0);
	assert(camera_y >= 0);

	// Init-Function Logs
    log("Render GameManager has been called", GameManager);

	current_scene->render(0,0);

	// Mid-Function Logs
    log("render -> current_scene has called render(0,0)", GameManager);

	if (render_quit_box) {
		message_box->render(0,0);

		// Mid-Function Logs
	    log("render -> message_box has called render(0,0)", GameManager);
	}

	else {
		// Nothing to do
	}

	fade_screen->render(0,0);

	// Post-Function Logs
    log("render -> fade_screen has called render(0,0)", GameManager);
	log("render has ended", GameManager);
}

/**
 * Responsible for running the GameManager
**/
void GameManager::run() {

	// Init-Function Logs
    log("Run GameManager has been called", GameManager);

	while(!SDL_QuitRequested()) {

		frame_start = SDL_GetTicks();
		dt = frame_start - frame_end;

		// Tests
	    TEST_CASE("Testing run (GameManager)", "[GameManager]") {
			REQUIRE(frame_start == SDL_GetTicks);
			REQUIRE(dt == (frame_start - frame_end));
		}

		// Mid-Function Logs
		log("render -> frame_start has called SDL_GetTicks()", GameManager);
		log("render -> dt = " + dt, GameManager);

		if (current_scene->should_change_scene() && fade_screen->isFaded()) {
			current_scene->Exit();
			current_scene = current_scene->getNextScene();
			current_scene->Enter();

			// Mid-Function Logs
		    log("render -> current_scene has called Exit()", GameManager);
			log("render -> current_scene has called getNextScene", GameManager);
			log("render -> current_scene has called Enter()", GameManager);
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

			// Mid-Function Logs
		    log("render has called processEvents()", GameManager);
			log("render has called update(dt)", GameManager);
			log("render has called render(camera_x1, camera_y1)", GameManager);
			log("render has called SDL::updateScreen()", GameManager);
			log("render -> frame_end has called SDL_GetTicks", GameManager);

		}

		else {
			SDL_Delay(1000/30 -dt);
		}

		this->current_scene->clean_destroyed_game_objects();

		// Post-Function Logs
		log("render -> current_scene has called clean_destroyed_game_objects()", GameManager);
	}

	// Post-Function Logs
	log("run has ended", GameManager);
}
