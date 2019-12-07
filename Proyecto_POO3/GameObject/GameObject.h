#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"

class GameObject
{
public:
	enum SPACE { local = 0, world = 1 };
	GameObject(float x = 0, float y = 0);
	~GameObject();

	void Position(Vector2 position);
	Vector2 Position(SPACE space = world);

	void Active(bool active);
	bool Active();
	void Translate(Vector2 vec);



private:
	Vector2 Pos;
	bool active;

	virtual void Update();
	virtual void Render();
};


#endif // !GAMEOBJECT_H