

#ifndef FADESCREEN_H_
#define FADESCREEN_H_
#include "GameObject.h"
#include "Sprite.h"
#include "FadeHandler.h"

class FadeScreen : GameObject {
public:
	FadeScreen(float x, float y);
	virtual ~FadeScreen();
	int update(int dt);
	void render(float camera_x, float camera_y);
	bool isFaded();
	void fade_out(float percentage, float time);
	void fade_in(float percentage, float time);

private:
	Sprite * sprite;
	FadeHandler * fadeHandler;
};

#endif /* FADESCREEN_H_ */
