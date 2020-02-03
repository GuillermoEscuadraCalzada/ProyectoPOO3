#include "GameObject.h"
#include <algorithm>
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

void GameObject::SeekSB(Vector2 target)
{
	try
	{

		Vector2 steering;
		float desired_VelocityX = normalizeVector(target).x * max_speed;
		float desired_VelocityY = normalizeVector(target).y * max_speed;
		steering.x = desired_VelocityX - speed;
		steering.y = desired_VelocityY - speed;

		if(steering.x < speed || steering.y < speed)
		{
			Vector2* clampedVector = new Vector2(steering.x + speed, steering.y + speed);
			Pos.x += clampedVector->x;
			Pos.y += clampedVector->y;
		} else if(steering.x > max_speed || steering.y > max_speed)
		{
			Vector2* clampedVector = new Vector2(max_speed, max_speed);
			Pos.x += clampedVector->x;
			Pos.y += clampedVector->y;

		}
	} catch(std::exception & e)
	{
		std::cout << "Exception caught: " << e.what() << "\n";
	}
}

Vector2 GameObject::normalizeVector(Vector2 target)
{
	Vector2 distance = target - Pos;
	float sqrRoot = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	Vector2 normalized;
	normalized.x = distance.x / sqrRoot;
	normalized.y = distance.y / sqrRoot;
	std::cout << "Normalized Vector.x: " << normalized.x << "\nNormalized Vector.y: " << normalized.y << "\n";
	return normalized;
}

void GameObject::Update()
{
}

void GameObject::Render()
{
}
