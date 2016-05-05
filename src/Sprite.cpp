#include "Sprite.h"

/*
 * Class constructor, sets the sprite's surface as a null and loads
 * An image on it
 */
Sprite::Sprite(std::string file) {
	surface = NULL;
	load(file);
	currentAlpha = 255;
	numberRef = 0;
}

/*
 * Class destructor, releases the surface's pointer of the Sprite
 */
Sprite::~Sprite() {
	if (surface) {
		SDL_FreeSurface(surface);
	}

	else {
		// Nothing to do
	}
}

/*
 * Function that loads an image at the surface and crops the clip_rect to
 * It's surface
 */
void Sprite::load(std::string file) {
	if (surface) {
		SDL_FreeSurface(surface);
	}

	else {
		// Nothing to do
	}
		surface = SDLBase::loadImage(file);
		clipRect.x = 0;
		clipRect.y = 0;
		clipRect.w = surface->w;
		clipRect.h = surface->h;
}

/*
 * Function that sets the variables of clip_rect
 */
void Sprite::clip(int x, int y, int w, int h) {
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

/*
 * Fuction that returns the clip_rect
 */
SDL_Rect Sprite::getClip() {
	return clipRect;
}

/*
 * Function that pastes the surface of the sprite in a position of the
 * Main buffer
 */
void Sprite::render(float x, float y) {
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = 0;
	dst.h = 0;

	SDLBase::renderSurface(surface, &clipRect, &dst);
}

/*
 * Function that returns the width of the sprite's surface
 */
int Sprite::getWidth() {
	return surface->w;
}

/*
 * Function that returns the height of the sprite's surface
 */
int Sprite::getHeight() {
	return surface->h;
}

int Sprite::getAlpha() {
	return currentAlpha;
}

void Sprite::setAlpha(int alpha) {
	if (alpha < 0) {
			alpha = 0;
	}

	else if (alpha > 255) {
		alpha = 255;
	}

	else {
		// Nothing to do
	}

	currentAlpha = alpha;
	SDLBase::setAlpha(surface, currentAlpha);
}

void Sprite::incNumRef() {
	this->numberRef++;
}

void Sprite::decNumRef() {
	this->numberRef--;
}

int Sprite::getNumRef() {
	return this->numberRef;
}
