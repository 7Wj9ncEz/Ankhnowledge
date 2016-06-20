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
	Scene(string scene_name);
	virtual ~Scene();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	void add_scenes(Scene * scene);
	int change_scene(string scene_name);
	string * getName();
	bool should_change_scene();
	list<GameObject *> getAllGameObject();
	virtual int update(int detective);
	virtual void render(float camera_x, float camera_y);
	Scene * getNextScene();
	void destroy_game_object(GameObject * gameObject);
	void clean_destroyed_game_objects();
	string get_scene_name();

protected:
	list<Scene *> scenes;
	list<GameObject *> gameObjects;
	string scene_name;
	bool sChangeScene;
	Scene * nextScene;
	void addGameObject(GameObject * gameObject);
	void clean_game_objects();
	vector<GameObject*> garbage;
};

#endif /* SCENE_H_ */
