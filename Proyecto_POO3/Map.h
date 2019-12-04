#ifndef MAP_H
#define MAP_H
#include <iostream>

template<class T, class S>
class MapNode
{
	T key;
	S value;
	MapNode<T, S>* next;
};


template<class T, class S>
class Map
{
public:
	Map();
	~Map();

	void insert(T key, S value);

	void print(T key, S value);

};



template<class T, class S>
inline Map<T, S>::Map()
{
}

template<class T, class S>
inline Map<T, S>::~Map()
{
}

template<class T, class S>
inline void Map<T, S>::insert(T key, S value)
{
	try
	{
		MapNode<T, S>* temp = new MapNode(value);



	} catch(std::exception & e)
	{
		std::cout << "Exception cuaght: " << e.what() << std::endl;
	} catch(...)
	{

	}
}

#endif // !MAP_H