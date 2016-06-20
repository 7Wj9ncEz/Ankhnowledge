

#ifndef FADEHANDLER_H_
#define FADEHANDLER_H_
#include "SDLBase.h"
#include "Sprite.h"

class FadeHandler {
public:
	FadeHandler(Sprite* sprite);
	virtual ~FadeHandler();
	void fade_in(float percentage, float time);
	void fade_out(float percentage, float time);
	void update(float detective);
	float get_current_percentage();
private:
	bool should_fade_in;
	bool should_fade_out;
	float percentage_of_stop;
	Sprite * sprite;
	float time;
	float current_percentage;
	float rate;
};

#endif /* FADEHANDLER_H_ */
