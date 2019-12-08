#include "GameObject.h"

/*Este constructo de game object, setea la posici�n del objeto en el lugar indicado
	@param[ x ] posici�n en x dentro de la pantalla
	@param[ y ] posici�n en y dentro de la pantalla*/
GameObject::GameObject(float x, float y)
{
	Pos.x = x;	//El vector Pos recibe en su vector x el float x
	Pos.y = y;	//El vecto Pos recibe en su vector y el float y

	active = true;	//Se vuelve verdadero
}

GameObject::GameObject(Vector2 pos)
{
	Pos = pos;
}

/*Destructro de la clase GameObject*/
GameObject::~GameObject()
{
}

/*El vector position se iguala al vector del argumento
	@param[ position ] Este argumento ser� la posi�n del objeto*/
void GameObject::Position(Vector2 position)
{
	Pos = position;
}


Vector2 GameObject::Position(SPACE space)
{

	return Pos;
}

/*Cuando deje de estar activo, la terminar� y se detendr� en el �ltimo sprite
	@param[active] el active de la clase cambia dependiendo al par�metro*/
void GameObject::Active(bool active)
{
	this->active = active;
}

/*Regresa si active es verdadero o falsoe
	@return verdadero o falso*/
bool GameObject::Active()
{
	return active;
}

/*Translate cambia la posicion de acuerdo al vector dentro del par�metro
	@param[Vector 2 vec] vector que modificar� la posici�n del objeto*/
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
