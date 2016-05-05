#include "SDLBase.h"
#include "math.h"
#include <iostream>

using namespace std;
SDL_Surface* SDLBase::screen;

/*
 * Construtor da Classe
 */
SDLBase::SDLBase() {
	// TODO Auto-generated constructor stub

}

/*
 * Destrutor da Classe
 */
SDLBase::~SDLBase() {
	// TODO Auto-generated destructor stub
}

/*
 * Metodo responsavel por inicializar a biblioteca do SDL. Alem disso, cria uma janela
 * e uma surface para renderizacao
 */
int SDLBase::initializeSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("Ankhnowledge", "Ankhnowledge");
	return 0;
}

/*
 * Metodo que retorna a surface de renderizacao. No caso como a tecnica utlizada e
 * double buffering, entao o retorno e o buffer principal
 */
SDL_Surface* SDLBase::getScreen() {
	return screen;
}

/*
 * Metodo que retorna uma superficie com uma imagem carregada. Esse metodo leva em
 * consideracao se a imagem utiliza ou nao o canal alpha
 */
SDL_Surface* SDLBase::loadImage(std::string arquivo){
	SDL_Surface *surface = NULL;
		SDL_Surface *surtemp;
		surface = IMG_Load(arquivo.c_str());
		if (surface->format->Amask){
			surtemp = SDL_DisplayFormatAlpha(surface);

		}else{
			surtemp = SDL_DisplayFormat(surface);
		}
		SDL_FreeSurface(surface);
		return surtemp;
}

void SDLBase::fillRectangle(SDL_Rect* rect, Uint32 color) {

	SDL_FillRect(screen, rect, color);
}

/*
 * Metodo que "cola" uma superficie em outra superficie. Metodo que possibilita a tecnica
 * do double buffering
 */
void SDLBase::renderSurface(SDL_Surface* surface, SDL_Rect* clip, SDL_Rect* dst){
	SDL_BlitSurface(surface, clip, screen, dst);
}

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

	if (x2 >= x1)              // The x-values are increasing
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                       // The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)              // The y-values are increasing
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                       // The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)		// There is at least one x-value for every y-value
	{
		xinc1 = 0;				// Don't change the x when numerator >= denominator
		yinc2 = 0;				// Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;		// There are more x-values than y-values
	}
	else						// There is at least one y-value for every x-value
	{
		xinc2 = 0;				// Don't change the x for every iteration
		yinc1 = 0;				// Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;		// There are more y-values than x-values
	}

	for (int curpixel = 1; curpixel <= numpixels; curpixel++)
	{
		if (spacing == 0)
		{
			SDL_Rect pixel;
			pixel.x = x;
			pixel.y = y;
			pixel.w = 4;
			pixel.h = 4;
			SDL_FillRect(screen,&pixel,rgb);
		}
		else if (curpixel % spacing >= spacing/2)
		{
			SDL_Rect pixel;
			pixel.x = x;
			pixel.y = y;
			pixel.w = 1;
			pixel.h = 1;
			SDL_FillRect(screen,&pixel,rgb);
		}

		num += numadd;         // Increase the numerator by the top of the fraction
		if (num >= den)        // Check if numerator >= denominator
		{
			num -= den;         // Calculate the new numerator value
			x += xinc1;         // Change the x as appropriate
			y += yinc1;         // Change the y as appropriate
		}
		x += xinc2;             // Change the x as appropriate
		y += yinc2;             // Change the y as appropriate
	}
}

void SDLBase::putpixel(SDL_Surface* screen, int x, int y,int r, int g, int b)
{
    Uint32 *pixel = (Uint32*)screen->pixels;
    Uint32 *p = pixel + y*screen->pitch/4 + x;
    *p = SDL_MapRGB(screen->format, r,g,b);
}

//Draw a filled circle
void SDLBase::drawCircle(float size, int x,int y,int r, int g, int b)
{
	for(int s = size;s>0;s--){
		for(int i = 0; i<=360; i++)
		{
			putpixel(screen, (x + (s*cos(i))), (y + (s*sin(i))),r,g,b);
		}
	}
}

/*
 * Metodo para atualizar o buffer principal
 */
void SDLBase::updateScreen(){
	SDL_Flip(screen);
}

void SDLBase::setAlpha(SDL_Surface * surface, int alpha)
{
	SDL_SetAlpha(surface ,SDL_RLEACCEL | SDL_SRCALPHA,(Uint8)alpha);
}

int SDLBase::getTime()
{
	return SDL_GetTicks();
}

void SDLBase::initializeSDLTTF(){
	int rc = TTF_Init();

	if (rc != 0)
	{
	fprintf(stderr, "Erro na inicializacao da SDL_ttf: %s\n",TTF_GetError());
	}
	atexit(TTF_Quit);
}

TTF_Font* SDLBase::loadFont(const char* fontName,int size){
	TTF_Font *font;
	font = TTF_OpenFont(fontName, size);

	if (!font) {
		fprintf(stderr, "Nao foi possivel carregar a font: %s\n",TTF_GetError());
	}

	return font;

}

void SDLBase::renderText(TTF_Font*font, string text,SDL_Color color,float x,float y){
	SDL_Surface * renderedText = TTF_RenderText_Solid(font, text.c_str(), color);

	if (!renderedText) {
		fprintf(stderr, "Falha na renderizacao do texto: %s\n",
			TTF_GetError());
		TTF_CloseFont(font);
	}

	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	dst.w = 0;
	dst.h = 0;

	renderSurface(renderedText, NULL, &dst);

}
