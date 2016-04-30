#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <stdlib.h>
#include "SDL/SDL.h"

class InputManager {
public:
	virtual ~InputManager();
	static InputManager* getInstance();
	void Update();
	bool isKeyDown(int key);
	bool isKeyUp(int key);
	bool isKeyPressed(int key);
	bool isMouseDown(int button);
	bool isMouseUp(int button);
	bool isMousePressed(Uint8 button);
	int mousePosX();
	int mousePosY();
	bool isMouseInside(SDL_Rect * rect);
	bool QuitGame();

private:
	InputManager();
	Uint8 mouse, *keyboard;
	Uint8 keyDown[256], keyUp[256];
	bool quitGame;
	Uint8 mouseDown[256], mouseUp[256];
	int mouse_x, mouse_y;
	static InputManager *instance;
};

#endif /* INPUTMANAGER_H_ */
