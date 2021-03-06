#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"

class GameObject
{
public:
	enum SPACE { local = 0, world = 1 };
	GameObject(float x = 0, float y = 0);
	GameObject(Vector2 pos);
	~GameObject();

	void Position(Vector2 position);
	Vector2 Position(SPACE space = world);
	Vector2 GetPosition() {
		return Pos;
	};
	Vector2 addFloat(float x, float y)
	{
		Pos.x += x;
		Pos.y += y;
		return Pos;
	}
	void Active(bool active);
	bool Active();
	void Translate(Vector2 vec);
	void SeekSB(Vector2 target);
	float max_speed = 8;
	float speed = 2;
	void setMaxSpeed(float _maxSpeed)
	{
		max_speed = _maxSpeed;
	}

	Vector2 normalizeVector(Vector2 target);

private:
	Vector2 Pos;
	bool active;

	virtual void Update();
	virtual void Render();
};


#endif // !GAMEOBJECT_H