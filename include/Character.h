#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Network.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameManager.h"
#include "Animation.h"
#include "Tile.h"
#include "Skill.h"
#include <string>
#include "Map.h"

class Tile;
class Skill;
class Map;

class Character:public GameObject {
	public:
		Character(Tile* tile, int id);
		void render(float camera_x, float camera_y);
		virtual int update(int dt);
		virtual ~Character();
		bool isUsingSkill();
		bool isPerformingAction();
		enum Direction { up, down, right, left, none };
		virtual void pushUpdate(InputManager * input, Direction dir = none);
		virtual void moveUpdate(InputManager * input, Direction dir = none);
		virtual void move(Direction dir);
		void setSkill(Skill * skill);
		virtual void setSkillDestTile(Tile * tile);
		virtual void push(Direction dir);
		void interpolateMovement(float dt);
		void setTurn(bool on);
		void toogleTurn();
		int getStamina();
		int getInitialStamina();
		void setStamina(int stamina);
		int getId();
		void setCurrentTile(Tile * tile);
		Tile * getCurrentTile();
		void incrementDiscountStamina(int value);
		void resetDiscountStamina();
		bool hasEnoughStamina();
		bool getWin();
		void setWin(bool win);
		bool getTurn();
		Sprite * getHud();
		void activateSkill();
		void deactivateSkill();
		void useSkill(int tileIndex);
		void setMap(Map * map);
		void send_message(string action, string info);
		void spawnSand(string msg);

	protected:
		Sprite* sprite, *hud;
		Animation *currentAnimation;
		Skill* skill;
		float vx,vy;
		bool activatedSkill;
		bool performingAction,on_loop;
		float end_x;
		float end_y;
		float begin_x;
		float begin_y;
		int stamina;
		int initialStamina;
		bool win;
		bool turn;
		int id;
		int dt;
		int direction;
		Tile * currentTile, * skillDestTile;
		virtual void changeCurrentTile(Tile * tile);
		virtual bool canChangeTile(Tile * tile);
		void setClickableTiles(Tile *origin, int reach, bool considerBlock, bool clickable);
		int discountStamina;
		void receive_message();
		string intToString(int intenger);
		Map * map;
};

#endif /* CHARACTER_H_ */
