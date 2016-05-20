#ifndef SDLBASE_H_
#define SDLBASE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class SDLBase {
public:
	SDLBase();
	virtual ~SDLBase();
	static int initializeSDL();
	static SDL_Surface* getScreen();
	static SDL_Surface* loadImage(std::string file);
	static void renderSurface(SDL_Surface* surface, SDL_Rect* clip = NULL, SDL_Rect* dst = NULL);
	static void updateScreen();
	static void fillRectangle(SDL_Rect* rect, Uint32 color);
	static void drawLine(int initial_x, int initial_y, int final_x, int final_y, int rgb, int spacing);
	static void putpixel(SDL_Surface* screen, int x, int y,int r,int g,int b);
	static void drawCircle(float size, int x,int y,int r, int g, int b);
	static void setAlpha(SDL_Surface * surface, int alpha);
	static int getTime();
	static string resourcesPath;
	static void initializeSDLTTF();
	static TTF_Font* loadFont(const char* font_name,int size);
	static void renderText(TTF_Font*font,string text,SDL_Color color,float x,float y);
private:
	static SDL_Surface* screen;
};

#endif /* SDLBASE_H_ */
