/*
 * SceneSelectCharacter.h
 *
 *  Created on: Nov 21, 2013
 *      Author: makoto
 */

#ifndef SCENESELECTCHARACTER_H_
#define SCENESELECTCHARACTER_H_

#include "Scene.h"
#include "SelectCharacterController.h"
#include <string>
class SelectCharacterController;


class SceneSelectCharacter : public Scene {
public:
	SceneSelectCharacter(string scene_name);
	virtual ~SceneSelectCharacter();
	void Enter();
	void Exit();

private:

	SelectCharacterController* cc;
};

#endif /* SCENESELECTCHARACTER_H_ */
