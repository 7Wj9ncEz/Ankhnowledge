#include "SDLBase.h"
#include "math.h"
#include <iostream>
#include <assert.h>

using namespace std;
SDL_Surface* SDLBase::screen;

/**
 * Class constructor
**/
SDLBase::SDLBase() {
	// TODO Auto-generated constructor stub

}

/**
 * Destrutor da Classe
**/
SDLBase::~SDLBase() {
	// TODO Auto-generated destructor stub
}

/**
 * Function that initializes the SDL library
 * Also it creates a window and a surface for rendering
**/
int SDLBase::initializeSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("Ankhnowledge", "Ankhnowledge");
	return 0;
}

/**
 * Function that returns the rendering surface
**/
SDL_Surface* SDLBase::getScreen() {
	return screen;
}

/**
 * Function that returns a surface with a loaded image
 * This function takes into consideration if the image uses or not the alpha channel
**/
SDL_Surface* SDLBase::loadImage(std::string file){

	// Asserts
	assert(file != NULL);

	SDL_Surface *surface = NULL;
		SDL_Surface *temporary_surface;
		surface = IMG_Load(file.c_str());
		if (surface->format->Amask) {
			temporary_surface = SDL_DisplayFormatAlpha(surface);

		}

		else {
			temporary_surface = SDL_DisplayFormat(surface);
		}

		SDL_FreeSurface(surface);
		return temporary_surface;
}

/**
 * Fills a rectangle with a color
 *
 * Parameters:
 * "rect" is a SDL_Rect pointer that references to a rectangle object
 * "color" in a scale of Uint32 will fill the rectangle with it's details
**/
void SDLBase::fillRectangle(SDL_Rect* rect, Uint32 color) {

	// Asserts
	assert(rect != NULL);
	assert(color != NULL);

	SDL_FillRect(screen, rect, color);
}

/**
 * Function that sticks a surface on another surface
 * This function allows the technique of double buffering
**/
void SDLBase::renderSurface(SDL_Surface* surface, SDL_Rect* clip, SDL_Rect* dst){

	// Asserts
	assert(surface != NULL);
	assert(clip != NULL);
	assert(dst != NULL);

	SDL_BlitSurface(surface, clip, screen, dst);
}

/**
 * Draws a line corresponding to the coordinates
 *
 * Parameters:
 * "initial_x & initial_y" initial positions (in pixels) of the line
 * "final_x & final_y" ending positions (in pixels) of the line
 * "rgb" code (in RGB scale) to color the line
 * "spacing" (in pixels) shows the size of the line
**/
void SDLBase::drawLine(int initial_x, int initial_y, int final_x, int final_y, int rgb, int spacing){

	// Asserts
	assert(initial_x >= 0);
	assert(final_x >= 0);
	assert(initial_y >= 0);
	assert(final_y >= 0);

	int delta_x = abs(final_x - initial_x); // The difference between the x's
	int delta_y = abs(final_y - initial_y); // The difference between the y's
	int x = initial_x;                // Start x off at the first pixel
	int y = initial_y;                // Start y off at the first pixel
	int x_increment_1 = 0;
	int y_increment_1 = 0;
	int x_increment_2 = 0;
	int y_increment_2 = 0;
	int denominator = 0;
	int num = 0;
	int numerator_add = 0;
	int number_pixels = 0;

	if (final_x >= initial_x) {             // The x-values are increasing
		x_increment_1 = 1;
		x_increment_2 = 1;
	}

	else {                      // The x-values are decreasing
		x_increment_1 = -1;
		x_increment_2 = -1;
	}

	if (final_y >= initial_y) {            // The y-values are increasing
		y_increment_1 = 1;
		y_increment_2 = 1;
	}

	else {                     // The y-values are decreasing
		y_increment_1 = -1;
		y_increment_2 = -1;
	}

	if (delta_x >= delta_y) {		// There is at least one x-value for every y-value
		x_increment_1 = 0;				// Don't change the x when numerator >= denominator
		y_increment_2 = 0;				// Don't change the y for every iteration
		denominator = delta_x;
		num = delta_x / 2;
		numerator_add = delta_y;
		number_pixels = delta_x;		// There are more x-values than y-values
	}

	else {						// There is at least one y-value for every x-value
		x_increment_2 = 0;				// Don't change the x for every iteration
		y_increment_1 = 0;				// Don't change the y when numerator >= denominator
		denominator = delta_y;
		num = delta_y / 2;
		numerator_add = delta_x;
		number_pixels = delta_y;		// There are more y-values than x-values
	}

	for (int current_pixel = 1; current_pixel <= number_pixels; current_pixel++) {
		if (spacing == 0) {
			SDL_Rect pixel;
			pixel.x = x;
			pixel.y = y;
			pixel.w = 4;
			pixel.h = 4;
			SDL_FillRect(screen, &pixel, rgb);
		}

		else if (current_pixel % spacing >= spacing/2) {
			SDL_Rect pixel;
			pixel.x = x;
			pixel.y = y;
			pixel.w = 1;
			pixel.h = 1;
			SDL_FillRect(screen, &pixel, rgb);
		}

		else {
			// Nothing to do
		}

		num += numerator_add;         // Increase the numerator by the top of the fraction
		if (num >= denominator) {        // Check if numerator >= denominator
			num -= denominator;         // Calculate the new numerator value
			x += x_increment_1;         // Change the x as appropriate
			y += y_increment_1;         // Change the y as appropriate
		}

		else {
			// Nothing to do
		}

		x += x_increment_2;             // Change the x as appropriate
		y += y_increment_2;             // Change the y as appropriate
	}
}

/**
 * Inserts a pixel in a screen
 *
 * Parameters:
 * "screen" is a surface from SDL library
 * "x & y" position (in pixels) that shows where to put the pixel
 * "r & g & b" represents the color scale of the "Red Green Blue"
**/
void SDLBase::putpixel(SDL_Surface* screen, int x, int y, int r, int g, int b) {

	// Asserts
	assert(screen != NULL);
	assert(x >= 0);
	assert(y >= 0);
	assert(r >= 0 && r <= 256);
	assert(g >= 0 && g <= 256);
	assert(b >= 0 && b <= 256);


	Uint32 *pixel = (Uint32*)screen->pixels;		// Receives the pixel from the screen
    Uint32 *p = pixel + y*screen->pitch/4 + x;		// Number of pixels + (y * screen_pitch/4) + x
    *p = SDL_MapRGB(screen->format, r,g,b);
}

/**
 * Draws a filled circle
 *
 * Parameters:
 * "size" represents the size (in pixels) of the circle
 * "x & y" coordinates (in pixels) to draw the circle
 * "r & g & b" represents the color scale of the "Red Green Blue"
**/
void SDLBase::drawCircle(float size, int x, int y, int r, int g, int b) {

	// Asserts
	assert(size > 1000);
	assert(x >= 0);
	assert(y >= 0);
	assert(r >= 0 && r <= 256);
	assert(g >= 0 && g <= 256);
	assert(b >= 0 && b <= 256);

	for(int s = size; s>0; s--) {
		for(int i = 0; i<=360; i++) {
			putpixel(screen, (x + (s*cos(i))), (y + (s*sin(i))), r, g, b);
		}
	}
}

/**
 * Function to update the primary buffer
**/
void SDLBase::updateScreen() {
	SDL_Flip(screen);
}

/**
 * Sets the Alpha in the surface's surface
 *
 * Parameters:
 * "surface" represents a Surface from SDL library
 * "alpha" coeficient of the alpha in the surface
**/
void SDLBase::setAlpha(SDL_Surface * surface, int alpha) {

	// Asserts
	assert(surface != NULL);
	assert(alpha >= 0 && alpha <= 1000);

	SDL_SetAlpha(surface, SDL_RLEACCEL | SDL_SRCALPHA, (Uint8)alpha);
}

/**
 * Shows the time of the game (in seconds)
**/
int SDLBase::getTime() {
	return SDL_GetTicks();
}

/**
 * Function to initialize the SDL True Type Fonts (TTF)
**/
void SDLBase::initializeSDLTTF() {
	int rc = TTF_Init();

	if (rc != 0) {
		fprintf(stderr, "Erro na inicializacao da SDL_ttf: %s\n", TTF_GetError());
	}

	else {
		// Nothing to do
	}
	atexit(TTF_Quit);
}

/**
 * loads a font to be used on the surface
 *
 * Parameters:
 * "font_name" shows which type of font it will be
 * "size" (in pixels) of the font
**/
TTF_Font* SDLBase::loadFont(const char* font_name, int size) {

	// Asserts
	assert(font_name != NULL);
	assert(size >= 0 && size > 1000);

	TTF_Font *font;
	font = TTF_OpenFont(font_name, size);

	if (!font) {
		fprintf(stderr, "Nao foi possivel carregar a font: %s\n",TTF_GetError());
	}

	else {
		// Nothing to do
	}

	return font;
}

/**
 * Renders a text on a surface
 *
 * Parameters:
 * "font" is a True Type Font (TTF)
 * "text" string that shows what's gonna be displayed
 * "color" scale (in SDL_Color scale) of the text
 * "x & y" positions (in pixels) of where the text will start
**/
void SDLBase::renderText(TTF_Font* font, string text, SDL_Color color, float x, float y) {

	// Asserts
	assert(font != NULL);
	assert(text != NULL);
	assert(color != NULL);
	assert(x >= 0);
	assert(y >= 0);

	SDL_Surface * renderedText = TTF_RenderText_Solid(font, text.c_str(), color);

	if (!renderedText) {
		fprintf(stderr, "Falha na renderizacao do texto: %s\n",
			TTF_GetError());
		TTF_CloseFont(font);
	}

	else {
		// Nothing to do
	}

	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = 0;
	dst.h = 0;

	renderSurface(renderedText, NULL, &dst);
}
