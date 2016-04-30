#ifndef SCENE_H_
#define SCENE_H_
#define SCENE_DOESNT_EXIST -1
#define SUCCESS 1;
#include <string>
#include <list>
#include <vector>
#include "GameObject.h"

using namespace std;

class Scene {
public:
	Scene(string sceneName);
	virtual ~Scene();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	void addScenes(Scene * scene);
	int change_scene(string sceneName);
	string * getName();
	bool shouldChangeScene();
	list<GameObject *> getAllGameObject();
	virtual int update(int dt);
	virtual void render(float camera_x, float camera_y);
	Scene * getNextScene();
	void destroyGameObject(GameObject * gameObject);
	void cleanDestroyedGameObjects();
	string getSceneName();

protected:
	list<Scene *> scenes;
	list<GameObject *> gameObjects;
	string sceneName;
	bool sChangeScene;
	Scene * nextScene;
	void addGameObject(GameObject * gameObject);
	void cleanGameObjects();
	vector<GameObject*> garbage;
};

#endif /* SCENE_H_ */
