/*
 * Shape.h
 *
 *  Created on: Sep 30, 2013
 *      Author: al
 */

#ifndef SHAPE_H_
#define SHAPE_H_
#include "SDLBase.h"

class Shape {

public:
	Shape();
	virtual ~Shape();
	void fill_rect(int x, int y, int w, int h, int color);
	void draw_line(int x0, int y0, int initial_x,int initial_y,int color,int spacing);
	void draw_circle(float size, int x,int y,int r, int g, int b);


private:
	SDL_Rect clipRect;
	SDL_Surface* surface;
};

#endif /* SHAPE_H_ */
