/*
 * OptionsController.h
 *
 *  Created on: Oct 28, 2013
 *      Author: al
 */

#ifndef OPTIONSCONTROLLER_H_
#define OPTIONSCONTROLLER_H_
#include "GameObject.h"
#include "Button.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Sprite.h"
#include <string>

using namespace std;

class OptionsController:public GameObject {
public:
	OptionsController();
	virtual ~OptionsController();
	void render(float camera_x, float camera_y);
	int update(int detective);
	void mouse_ouver(Button* bt);
	void mouse_pressed(Button* bt,string nextScene);
	void change_scene(string nextScene);

private:
	InputManager* input;
	Button *back;
	Sprite *back_1,*back_2,*back_3,*splashSprite;
	Sprite *sliderBar,*sliderButton;
	Slider * bgVolume,*soundEffect;
	int musicVolume, effectVolume;
	SDL_Color color;
	TTF_Font *font;
};

#endif /* OPTIONSCONTROLLER_H_ */
