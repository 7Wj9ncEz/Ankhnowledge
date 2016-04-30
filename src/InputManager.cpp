#include "InputManager.h"
#include <iostream>
InputManager * InputManager::instance = 0;

InputManager::InputManager() {
	// TODO Auto-generated constructor stub

}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
}

InputManager * InputManager::getInstance(){

	if(!instance) instance = new InputManager();
	return instance;
}

void InputManager::Update(){
	quitGame = 0;
	for(int i = 0; i < 256; i++){
		keyDown[i] = 0;
		keyUp[i] = 0;
		mouseDown[i] = 0;
		mouseUp[i] = 0;
	}

	keyboard = SDL_GetKeyState(NULL);
	mouse = SDL_GetMouseState(&mouse_x,&mouse_y);

	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:{
				keyDown[event.key.keysym.sym] = true;
				break;
			}
			case SDL_KEYUP:{
				keyUp[event.key.keysym.sym] = true;
				break;
			}
			case SDL_MOUSEMOTION:{
				//mouse = true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				mouseDown[event.key.keysym.sym] = true;
				break;
			}
			case SDL_MOUSEBUTTONUP:{
				mouseUp[event.key.keysym.sym] = true;
				break;
			}
			case SDL_QUIT:{
				quitGame = true;
				break;
			}
		}
	}
}

bool InputManager::isKeyDown(int key){
	if(keyDown[key])
		return true;

	return false;
}

bool InputManager::isKeyUp(int key){
	if(keyUp[key])
		return true;

	return false;
}

bool InputManager::isMouseDown(int key){
	if(mouseDown[key]){
		std::cout<<key<<std::endl;
		return true;
	}

	return false;
}

bool InputManager::isMouseUp(int key){
	if(mouseUp[key])
		return true;

	return false;
}

bool InputManager::isKeyPressed(int key){
	if(keyboard[key])
		return true;

	return false;
}

bool InputManager::isMousePressed(Uint8 button){
	if(mouse&SDL_BUTTON(button))
		return true;
	return false;
}

bool InputManager::isMouseInside(SDL_Rect * rect){
	if(mouse_x <= (rect->x+rect->w) && mouse_x >= rect->x && mouse_y <= (rect->y+rect->h) && mouse_y >= rect->y)
		return true;

	return false;
}

int InputManager::mousePosX(){
	return mouse_x;
}

int InputManager::mousePosY(){
	return mouse_y;
}

bool InputManager::QuitGame(){
	return quitGame;
}

