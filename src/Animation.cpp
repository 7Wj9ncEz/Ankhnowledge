/*
 * Animation.cpp
 *
 *  Class handles the rendering of all animations used
 *
 */

#include "Animation.h"
#include <assert.h>
#include "log.h"
#include "catch.hpp"

Animation::Animation(int sprite_width, int sprite_height, Sprite* sprite, int direction) {

    // Asserts
    assert(sprite != NULL);
    assert(sprite_width >= 0);
    assert(sprite_height >= 0);
    assert(sprite_width <= 1920);
    assert(sprite_height <= 1080);

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

    // Tests
    TEST_CASE("Testing Animation Constructor", "[Animation]") {
        REQUIRE(this->animation == sprite);
        REQUIRE(this->sprite_width = sprite_width);
        REQUIRE(this->sprite_height = sprite_height);
        REQUIRE(this->columns =  animation->getWidth() / sprite_width);
        REQUIRE(this->dt = 0);
        REQUIRE(this->start_frame = direction * columns);
        REQUIRE(this->previous_direction = direction);
        REQUIRE(this->current_frame = start_frame);
        REQUIRE(this->animate_sprite = true);
        REQUIRE(this->finished_animation = false);
    }

    // Logs
    log("Animation has been initialized", Animation);

}

Animation::~Animation() {
	// TODO Auto-generated destructor stub

    // Init-Function Logs
    log("Animation destructor called", Animation);

    // Post-Function Logs
    log("Animation destructor has ended", Animation);
}

/**
 * Renders all the animations in the Game
 *
 * Parameters:
 * "index" represents the options in the index for the player
 * "pos_x" shows the position of the animations
 * related to the X axis (it's limits depends on the player's resolution)
 * "pos_y" shows the position of the animations
 * related to the Y axis (it's limits depends on the player's resolution)
**/
void Animation::render(int index, float pos_x, float pos_y) {

    // Asserts
    assert(index >= 0);
    assert(index <= 100);
    assert(pos_x >= 0);
    assert(pos_y >= 0);
    assert(pos_x <= 1920);
    assert(pos_y <= 1080);

    // Init-Function Logs
    log("Animation rendered", Animation);
    log("render -> index" + index, Animation);
    log("render -> pos_x" + pos_x, Animation);
    log("render -> pos_y" + pos_y, Animation);

	int x = index % columns;
	int y = index / columns;

	int clip_x = x * sprite_width;
	int clip_y = y * sprite_height;

    // Tests
    TEST_CASE("Testing render (Animation)", "[render]") {
        REQUIRE(x = index % columns);
        REQUIRE(y = index / columns);
        REQUIRE(clip_x = x * sprite_width);
        REQUIRE(clip_y = y * sprite_height);
    }

    // Mid-Function Logs
    log("render -> x" + x, Animation);
    log("render -> y" + y, Animation);
    log("render -> clip_x" + clip_x, Animation);
    log("render -> clip_y" + clip_y, Animation);

	animation->clip(clip_x, clip_y, sprite_width, sprite_height);
	animation->render(pos_x, pos_y);

    // Post-Function Logs
    log("render called clip()", Animation);
    log("animate called render()", Animation);
    log("render has ended", Animation);
}

void Animation::animate(int frame_rate, float pos_x, float pos_y) {

    // Asserts
    assert(frame_rate >= 0);
    assert(frame_rate <= 1000);
    assert(pos_x >= 0);
    assert(pos_y >= 0);
    assert(pos_x <= 1920);
    assert(pos_y <= 1080);

    // Init-Function Logs
    log("Animate function has been called", Animate);
    log("animate -> frame_rate" + frame_rate, Animation);
    log("animate -> pos_x" + pos_x, Animation);
    log("animate -> pos_y" + pos_y, Animation);

    this->frame_rate = frame_rate;

    // Tests
    TEST_CASE("Testing animate (Animation)", "[animate]") {
        REQUIRE(this->frame_rate = frame_rate);
    }

    // Mid-Function Logs
    log("animate -> frame_rate" + frame_rate, Animation);

    render(current_frame, pos_x, pos_y);

    // Post-Function Logs
    log("animate called render()", Animation);
    log("animate has ended", Animation);
}

/**
 * Updates all the animations in the Game
 *
 * Parameters:
 * "on_loop" shows if the animation is under a loop or not
 * "direction" shows the direction of the animation towards an int
 * In a clockwise formation 0 is the top, 1 is the right and so goes on
 * "single_frame" shows if the animation will stand for a single frame or not
**/
void Animation::update(int dt, bool on_loop, int direction, bool single_frame) {

    // Asserts
    assert(dt >= 0);
    assert(dt <= 1000);

    // Init-Function Logs
    log("Update Animation has been called");
    log("update -> dt" + dt, Animation);
    log("update -> on_loop" + on_loop, Animation);
    log("update -> direction" + direction, Animation);
    log("update -> single_frame" + single_frame, Animation);

	this->dt = this->dt + dt;
	int last_frame = columns;

    // Tests
    TEST_CASE("Testing update (Animation)", "[update]") {
        REQUIRE(int last_frame = columns);
    }

    // Mid-Function Logs
    log("update -> dt" + dt, Animation);
    log("update -> last_frame" + last_frame, Animation);


	if (previous_direction != direction) {
		this->start_frame = direction * columns;
		this->current_frame = start_frame;
		this->previous_direction = direction;
		this->finished_animation = false;

        // Mid-Function Logs
        log("update -> start_frame" + start_frame, Animation);
        log("update -> current_frame" + current_frame, Animation);
        log("update -> previous_direction" + previous_direction, Animation);
        log("update -> finished_animation" + finished_animation, Animation);
	}

    else {
        // Nothing to do
    }

	if (single_frame) {
		last_frame = 1;
		this->finished_animation = false;

        // Mid-Function Logs
        log("update -> last_frame" + last_frame, Animation);
        log("update -> finished_animation" + finished_animation, Animation);
	}

    else {
        // Nothing to do
    }

	if ((this->dt > frame_rate)) {
        if ((current_frame == start_frame + last_frame -1) && (on_loop == true)) {
    			reset_start_frame();
    			finished_animation = false;

                // Mid-Function Logs
                log("update called reset_start_frame()", Animation);
                log("update -> finished_animation" + finished_animation, Animation);
		}

        else if ((current_frame == start_frame + last_frame -1) && (on_loop == false)) {
    			this->finished_animation = true;

                // Mid-Function Logs
                log("update -> finished_animation" + finished_animation, Animation);
		}

		else {
			current_frame++;
			this->dt = 0;

            // Mid-Function Logs
            log("update -> current_frame" + current_frame, Animation);
            log("update -> dt" + dt, Animation);
        }
	}

    else {
        // Nothing to do
    }

    // Post-Function Logs
    log("update has ended", Animation);
}

/**
 * Makes the "current_frame" variable receive the same value as the "start_frame"
 **/
void Animation::reset_start_frame() {

    // Init-Function Logs
    log("Reset Start Frame called", Animation);

	this->current_frame = start_frame;

    // Tests
    TEST_CASE("Testing reset_start_frame (Animation)", "[reset_start_frame]") {
        REQUIRE(this->current_frame = start_frame);
    }

    // Post-Function Logs
    log("reset_start_frame -> current_frame" + current_frame, Animation);
    log("reset_start_frame has ended", Animation);
}

/**
 * Regular getter for the variable "finished_animation"
**/
bool Animation::get_finished_animation() {

    // Init-Function Logs
    log("Get Finished Animation called", Animation);

    return this->finished_animation;

    // Post-Function Logs
    log("get_finished_animation has ended", Animation);
}
