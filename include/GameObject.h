#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class GameObject {
public:
	virtual ~GameObject();
	virtual int update(int dt) = 0;
	virtual void render(float camera_x, float camera_y) = 0;
	float getX();
	float getY();
	bool lerp(float begin_x, float begin_y, float end_x, float end_y, float time, float  dt);
	void setPosition(float x, float y);

protected:
	GameObject(float x, float y);
	float x;
	float y;

};

#endif /* GAMEOBJECT_H_ */
