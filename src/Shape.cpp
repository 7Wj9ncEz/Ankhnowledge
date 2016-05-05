/*
 * Shape.cpp
 *
 *  Created on: Sep 30, 2013
 *      Author: al
 */

#include "Shape.h"

Shape::Shape() {


}

Shape::~Shape() {
	if (surface){
		SDL_FreeSurface(surface);
	}
}

void Shape::fill_rect(int x, int y, int w, int h, int color){
	this->clipRect.x = x;
	this->clipRect.y = y;
	this->clipRect.w = w;
	this->clipRect.h = h;
	SDLBase::fillRectangle(&clipRect, color);
}

void Shape::draw_line(int x0, int y0,int x1, int y1,int color,int spacing){
	SDLBase::drawLine(x0,y0,x1,y1,color,spacing);
}

void Shape::draw_circle(float size, int x,int y,int r, int g, int b){
	SDLBase::drawCircle(size, x,y,r,g,b);
}
