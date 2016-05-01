/*
 * SceneSelectMap.h
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#ifndef SCENESELECTMAP_H_
#define SCENESELECTMAP_H_

#include "Scene.h"
#include "SelectMapController.h"
#include <string>
class SelectMapController;


class SceneSelectMap : public Scene {
public:
	SceneSelectMap(string scene_name);
	virtual ~SceneSelectMap();
	void Enter();
	void Exit();

private:

	SelectMapController* cc;
};

#endif /* SCENESELECTMAP_H_ */
