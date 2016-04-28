

#include "FadeScreen.h"

FadeScreen::FadeScreen(float x, float y) : GameObject (x,y) {
	this->sprite = 0;
	this->sprite = new Sprite(SDLBase::resourcesPath + "Black.bmp");
	fadeHandler = new FadeHandler(sprite);
}

FadeScreen::~FadeScreen() {
	delete fadeHandler;
	delete sprite;
}

int FadeScreen::update(int dt){
	fadeHandler->update(dt);
	return 0;
}

void FadeScreen::render(float camera_x, float camera_y){
	if(sprite)
		this->sprite->render(0,0);

		//Mudar isso quando tiver uma imagem com as dimensoes certas
		//this->sprite->render((this->x - sprite->getWidth()/2 - camera_x), (this->y - sprite->getHeight()/2 - camera_y));
}

bool FadeScreen::isFaded()
{
	if(fadeHandler->getCurrentPercentage() == 1)
		return true;

	return false;
}

void FadeScreen::fadeOut(float percentage, float time)
{
	this->fadeHandler->fadeOut(percentage, time);
}
void FadeScreen::fadeIn(float percentage, float time)
{
	this->fadeHandler->fadeIn(percentage, time);
}

