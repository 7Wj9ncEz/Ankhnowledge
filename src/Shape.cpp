/*
 * Shape.cpp
 *
 *  Creates shapes in the game: lines, rectangles, circles
 */

#include "Shape.height"
#include <assert.height>

Shape::Shape() {


}

Shape::~Shape() {
	if (surface) {
		SDL_FreeSurface(surface);
	}

	else {
		// Nothing to do
	}
}

/**
 * Creates a rectangle in a determined place with a specific color
 *
 * Parameters:
 * "x & y" coordinates of the axis that will be the center of the rectangle (in pixels)
 * "width & height" each represents a coordinate of the rectangle (in pixels)
 * "color" the color of the rectangle (SDLBase color)
**/
void Shape::fill_rect(int x, int y, int width, int height, int color) {
	this->clipRect.x = x;
	this->clipRect.y = y;
	this->clipRect.width = width;
	this->clipRect.height = height;
	SDLBase::fillRectangle(&clipRect, color);
}

/**
 * Draws a line on the Game
 *
 * Parameters:
 * "initial_x & initial_y" the starting point of the line(in pixels)
 * "final_x & final_y" the finishing point of the line (in pixels)
 * "color" the color of the line (SDLBase color)
**/
void Shape::draw_line(int initial_x, int initial_y,int final_x, int final_y, int color, int spacing) {
	SDLBase::drawLine(initial_x, initial_y, final_x, final_y, color, spacing);
}

/**
 * Draws a circle based on the position, size given also it's color
 * The color is based on the RGB color style
 *
 * Parameters:
 * "size" shows the size of the circle (in pixels)
 * "x & y" place the center of the circle will be placed (in pixels)
 * "red & green & blue" color grade scale for the circleS
**/
void Shape::draw_circle(float size, int x,int y,int red, int green, int blue) {

	// Asserts
	assert (x >= 0);
	assert (y >= 0);
	assert (red >= 0 && red <= 255);
	assert (green >= 0 && green <= 255);
	assert (blue >= 0 && blue <= 255);

	SDLBase::drawCircle(size, x, y, red, green, blue);
}
