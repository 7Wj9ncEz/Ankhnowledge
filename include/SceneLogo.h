
#ifndef SCENELOGO_H_
#define SCENELOGO_H_
#include "Scene.h"
#include "Sprite.h"
#include "SplashScreen.h"
#include <string>

class SceneLogo : public Scene{
public:
	SceneLogo(string scene_name);
	virtual ~SceneLogo();
	void Enter();
	void Exit();

private:
	Sprite * splashSprite;
};

#endif /* SCENELOGO_H_ */
