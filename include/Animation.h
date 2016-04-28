/*
 * Animation.h
 *
 *  Created on: Oct 27, 2013
 *      Author: al
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_
#include "Sprite.h"
#include <iostream>

using namespace std;

class Animation {
public:
	Animation(int sprite_width, int sprite_height, Sprite* sprite,int direction);
	virtual ~Animation();
	void render(int index, float pos_x, float pos_y);
	void animate(int frame_rate,float pos_x, float pos_y);
	void update(int dt,bool on_loop,int direction, bool single_frame);
	bool get_finished_animation();
	void reset_start_frame();

private:
	Sprite* animation;
	int sprite_width, sprite_height,columns;
	int current_frame,start_frame,dt,frame_rate;
	bool animate_sprite,finished_animation;
	int  previous_direction;
};

#endif /* ANIMATION_H_ */
