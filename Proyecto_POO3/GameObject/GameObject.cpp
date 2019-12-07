#include "GameObject.h"

GameObject::GameObject(float x, float y)
{
	Pos.x = x;
	Pos.y = y;

	active = true;

}

GameObject::~GameObject()
{
}

void GameObject::Position(Vector2 position)
{
	Pos = position;
}

Vector2 GameObject::Position(SPACE space)
{

	return Pos;
}

void GameObject::Active(bool active)
{
}

bool GameObject::Active()
{
	return active;
}

void GameObject::Translate(Vector2 vec)
{
	Pos += vec;
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}
