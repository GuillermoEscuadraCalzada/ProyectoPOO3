#ifndef  GRAPHLIST_H
#define GRAPHLIST_H
#include <iostream>
#include "../GameObject/Vector2.h"
using std::string; using std::exception; using std::cout; using std::endl;
//Clase nodo que se enocntrará dentro del grafo
template<class T>
class GraphNode
{
public:
	T value; //Cualquier valor que entre al template se guardará en el nodo
	Vector2 position;
	//GraphList<GraphNode*>* list;	//Una lista de nodos
	int index;	//Indice del nodo
	bool visited;	//Valor que determina si ya fue visitado o no

	/*Constructor de la clase nodo
		@param[T value] cualquier elemento que se añade a esta lista y se lo iguala al valor de la clase*/

	GraphNode<T>(T _value, Vector2 vec) : value(_value), position(vec)
	{
		visited = false;	//Visited empieza en falso
		index = 0;	//Indice es igual a cero
		//next = prev = top = bottom = nullptr;	//Los apuntadores empiezan en nulo
		//position = nullptr;
	};
	
	GraphNode<T>() {};
};



template<class T>
class GraphList
{
public:
	GraphNode<T>* next;	//Apuntador al siguiente elemento dentro del grafo
	GraphNode<T>* prev;	//Apuntador al elemento anterior dentro del grafo
	GraphNode<T>* top;	//Apuntador a una posición superior dentro del grafo
	GraphNode<T>* bottom;	//Apuntador que busca la posición inferior de este nodo
	//GraphNode<T>* first;
	//GraphNode<T>* last;
	int size;
	GraphList<T>();
	~GraphList<T>();

	void push_at(int index, GraphNode<T> value);
	void return_at_index(int index);
	void renderNode();
	void swap(int index, int _index);
	GraphNode<T> graphArr[8][8];
};

template<class T>
inline GraphList<T>::GraphList()
{
	try
	{
		size = 64;
		size = NULL;

	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	}
	catch(...)
	{
		cout << "Ups, something crashed!\n";
	}

}

template<class T>
inline GraphList<T>::~GraphList()
{
	try
	{

	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups, something crashed!\n";
	}
	
}

/*Esta fun*/
template<class T>
inline void GraphList<T>::push_at(int index, GraphNode<T> value)
{
	try{	
		GraphNode<T>* temp = new GraphNode<T>(value);
		for(int i = 0; i < size;i++ )
		{
			for(int j = 0; j < size; j++)
			{
				temp->index = index;
				graphArr[i][index] = temp;
			}
		}
	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups, something crashed!\n";
	}
}

template<class T>
inline void GraphList<T>::return_at_index(int index)
{
}

template<class T>
inline void GraphList<T>::renderNode()
{
	try
	{
		//GraphNode<T>* iterator = first;
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				//graphArr[i][j];
			}
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

template<class T>
inline void GraphList<T>::swap(int index, int _index)
{
}

#endif // ! GRAPHLIST_H