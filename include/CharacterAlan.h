#ifndef CHARACTERALAN_H_
#define CHARACTERALAN_H_

#include "Character.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Animation.h"
#include "Tile.h"
#include "Skill.h"

class Tile;
class Skill;
class Character;

class CharacterAlan:public Character {
  public:
    CharacterAlan(Tile* tile, int id);
    ~CharacterAlan();
};

#endif
