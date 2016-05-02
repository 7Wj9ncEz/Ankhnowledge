/*
 * Animation.cpp
 *
 *  Class handles the rendering of all animations used. 
 *
 *  Created on: Oct 27, 2013
 *      Author: al
 * 
 */

#include "Animation.h"
#include <assert.h>

Animation::Animation(int sprite_width, int sprite_height, Sprite* sprite, int direction) {

    // Asserts
    assert(sprite != NULL);
    assert(sprite_width >= 0);
    assert(sprite_height >= 0);

    // Makes a new sprite instance
    this->animation = sprite;
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    this->columns =  animation->getWidth() / sprite_width;
    this->dt = 0;
    this->start_frame = direction * columns;
    this->previous_direction = direction;
    this->current_frame = start_frame;
    this->animate_sprite = true;
    this->finished_animation = false;

}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

void Animation::render(int index, float pos_x, float pos_y) {

  // Asserts
  assert(index >= 0);
  assert(pos_x >= 0);
  assert(pos_y >= 0);

	int x = index % columns;
	int y = index / columns;

	int clip_x = x * sprite_width;
	int clip_y = y * sprite_height;

	animation->clip(clip_x, clip_y, sprite_width, sprite_height);
	animation->render(pos_x, pos_y);
}

void Animation::animate(int frame_rate, float pos_x, float pos_y) {

  // Asserts
  assert(frame_rate >= 0);

  this->frame_rate = frame_rate;
	render(current_frame, pos_x, pos_y);
}

void Animation::update(int dt, bool on_loop, int direction, bool single_frame) {

  // Asserts
  assert(dt >= 0);

	this->dt = this->dt + dt;
	int last_frame = columns;

	if (previous_direction != direction) {
		this->start_frame = direction * columns;
		this->current_frame = start_frame;
		this->previous_direction = direction;
		this->finished_animation = false;
	}

  else {
    // Nothing to do
  }

	if (single_frame) {
		last_frame = 1;
		this->finished_animation = false;
	}

  else {
    // Nothing to do
  }

	if ((this->dt > frame_rate)) {
		if ((current_frame == start_frame + last_frame -1) && (on_loop == true)) {
			reset_start_frame();
			finished_animation = false;
		}

    else if ((current_frame == start_frame + last_frame -1) && (on_loop == false)) {
			this->finished_animation = true;
		}

		else {
			current_frame++;
			this->dt = 0;
		}
	}

  else {
    // Nothing to do
  }

}

void Animation::reset_start_frame() {
	this->current_frame = start_frame;
}

bool Animation::get_finished_animation() {
	return this->finished_animation;
}
