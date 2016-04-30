#ifndef CHARACTERSUTI_H_
#define CHARACTERSUTI_H_

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

class CharacterSuti:public Character {
  public:
    CharacterSuti(Tile* tile, int id);
    ~CharacterSuti();
};

#endif
