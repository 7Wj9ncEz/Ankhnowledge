#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_
#include <stdlib.h>
#include "SDL/SDL.h"

class InputManager {
public:
	virtual ~InputManager();
	static InputManager* getInstance();
	void Update();
	bool is_key_down(int key);
	bool is_key_up(int key);
	bool is_key_pressed(int key);
	bool is_mouse_down(int button);
	bool is_mouse_up(int button);
	bool is_mouse_pressed(Uint8 button);
	int mouse_pos_x();
	int mouse_pos_y();
	bool is_mouse_inside(SDL_Rect * rect);
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
