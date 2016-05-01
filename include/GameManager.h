	
#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Sprite.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "InputManager.h"
#include "AudioHandler.h"
#include "Network.h"
#include "GameObject.h"
#include "Shape.h"
#include "FadeScreen.h"
#include "Scene.h"
#include "SceneLogo.h"
#include "SceneTechnology.h"
#include "SceneThirdParty.h"
#include "SceneLegal.h"
#include "SceneMainMenu.h"
#include "ScenePhaseOne.h"
#include "ScenePhaseTwo.h"
#include "ScenePhaseThree.h"
#include "ScenePhaseFour.h"
#include "ScenePhaseFive.h"
#include "SceneGameOver.h"
#include "SceneCredits.h"
#include "SceneOptions.h"
#include "SceneSelectMap.h"
#include "SceneSelectCharacter.h"
#include "MessageBox.h"

class GameManager {
public:
	GameManager();
	virtual ~GameManager();
	void run();
	void processEvents();
	void update(int dt);
	void render(float camera_x, float camera_y);
	void initResources();
	static FadeScreen * fadeScreen;
	static Scene * currentScene;

private:
	Sprite* bg,*box_spr;
	Scene * splashLogo;
	Scene * splashTechnology;
	Scene * splashThirdParty;
	Scene * splashLegal;
	Scene * splashMainMenu;
	Scene * splashPhaseOne;
	Scene * splashPhaseTwo;
	Scene * splashPhaseThree;
	Scene * splashPhaseFour;
	Scene * splashPhaseFive;
	Scene * splashGameOver;
	Scene * splashCredits;
	Scene * splashOptions;
	Scene * splashConnect;
	Scene * splashSelectMap;
	Scene * splashSelectCharacter;
	MessageBox * mb;
	InputManager * input;
	AudioHandler * audio;
	Shape* shape;
	std::vector<GameObject*> gameObjects;
	float SCROLL;
	float cameraX1;
	float cameraX2;
	float cameraY1;
	float cameraY2;
	float camera_speed_x;
	float camera_speed_y;
	float fatorParallaxScrolling;
	int dt, frame_start, frameEnd;
	bool quit, renderQuitBox, escPressed;


};

#endif /* GAMEMANAGER_H_ */
