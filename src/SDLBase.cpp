#include "SDLBase.h"
#include "math.h"
#include <iostream>

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
SDL_Surface* SDLBase::loadImage(std::string arquivo){
	SDL_Surface *surface = NULL;
		SDL_Surface *surtemp;
		surface = IMG_Load(arquivo.c_str());
		if (surface->format->Amask) {
			surtemp = SDL_DisplayFormatAlpha(surface);

		}

		else {
			surtemp = SDL_DisplayFormat(surface);
		}

		SDL_FreeSurface(surface);
		return surtemp;
}

/**
 * Fills a rectangle with a color
 *
 * Parameters:
 * "rect" is a SDL_Rect pointer that references to a rectangle object
 * "color" in a scale of Uint32 will fill the rectangle with it's details
**/
void SDLBase::fillRectangle(SDL_Rect* rect, Uint32 color) {

	SDL_FillRect(screen, rect, color);
}

/**
 * Function that sticks a surface on another surface
 * This function allows the technique of double buffering
**/
void SDLBase::renderSurface(SDL_Surface* surface, SDL_Rect* clip, SDL_Rect* dst){
	SDL_BlitSurface(surface, clip, screen, dst);
}

/**
 * Draws a line corresponding to the coordinates
 *
 * Parameters:
 * "x1 & y1" initial positions (in pixels) of the line
 * "x2 & y2" ending positions (in pixels) of the line
 * "rgb" code (in RGB scale) to color the line
 * "spacing" (in pixels) shows the size of the line
**/
void SDLBase::drawLine(int x1, int y1, int x2, int y2, int rgb, int spacing){
	int deltax = abs(x2 - x1); // The difference between the x's
	int deltay = abs(y2 - y1); // The difference between the y's
	int x = x1;                // Start x off at the first pixel
	int y = y1;                // Start y off at the first pixel
	int xinc1 = 0;
	int yinc1 = 0;
	int xinc2 = 0;
	int yinc2 = 0;
	int den = 0;
	int num = 0;
	int numadd = 0;
	int numpixels = 0;

	if (x2 >= x1) {             // The x-values are increasing
		xinc1 = 1;
		xinc2 = 1;
	}

	else {                      // The x-values are decreasing
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {            // The y-values are increasing
		yinc1 = 1;
		yinc2 = 1;
	}

	else {                     // The y-values are decreasing
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay) {		// There is at least one x-value for every y-value
		xinc1 = 0;				// Don't change the x when numerator >= denominator
		yinc2 = 0;				// Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;		// There are more x-values than y-values
	}

	else {						// There is at least one y-value for every x-value
		xinc2 = 0;				// Don't change the x for every iteration
		yinc1 = 0;				// Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;		// There are more y-values than x-values
	}

	for (int curpixel = 1; curpixel <= numpixels; curpixel++) {
		if (spacing == 0) {
			SDL_Rect pixel;
			pixel.x = x;
			pixel.y = y;
			pixel.w = 4;
			pixel.h = 4;
			SDL_FillRect(screen,&pixel,rgb);
		}

		else if (curpixel % spacing >= spacing/2) {
			SDL_Rect pixel;
			pixel.x = x;
			pixel.y = y;
			pixel.w = 1;
			pixel.h = 1;
			SDL_FillRect(screen,&pixel,rgb);
		}

		else {
			// Nothing to do
		}

		num += numadd;         // Increase the numerator by the top of the fraction
		if (num >= den) {        // Check if numerator >= denominator
			num -= den;         // Calculate the new numerator value
			x += xinc1;         // Change the x as appropriate
			y += yinc1;         // Change the y as appropriate
		}

		else {
			// Nothing to do
		}

		x += xinc2;             // Change the x as appropriate
		y += yinc2;             // Change the y as appropriate
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
void SDLBase::putpixel(SDL_Surface* screen, int x, int y,int r, int g, int b) {
    Uint32 *pixel = (Uint32*)screen->pixels;
    Uint32 *p = pixel + y*screen->pitch/4 + x;
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
	for(int s = size;s>0;s--) {
		for(int i = 0; i<=360; i++) {
			putpixel(screen, (x + (s*cos(i))), (y + (s*sin(i))),r,g,b);
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
	SDL_SetAlpha(surface ,SDL_RLEACCEL | SDL_SRCALPHA,(Uint8)alpha);
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
		fprintf(stderr, "Erro na inicializacao da SDL_ttf: %s\n",TTF_GetError());
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
TTF_Font* SDLBase::loadFont(const char* font_name,int size) {
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
