#ifndef GRAPH_H
#define GRAPH_H
#include  "GraphList.h"
using std::exception; using std::string; using std::cout; using std::endl;
template<class T>
class Graph
{
public:
	Graph<T>();
	~Graph<T>();
	GraphNode<T>* father;
	GraphList<T>* list;
	int size;
	void InsertNode(int index, GraphNode<T>* father);
	void delete_node_Content(GraphNode<T>* Node);
};

template<class T>
inline Graph<T>::Graph()
{
}

template<class T>
inline Graph<T>::~Graph()
{
}

/*Inserta un valor dentro del padre especificado
	@param[T data] valor del template que quiera entrar
	@param[GraphNode<T>* father ] padre del nodo que irá haciendo recursividad hasta llegar al espacio vacío*/
template<class T>
inline void Graph<T>::InsertNode(int index, GraphNode<T>* father)
{
	try
	{

				list->push_at(index, father);

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

template<class T>
inline void Graph<T>::delete_node_Content(GraphNode<T>* Node)
{
}

#endif //!GRAPH_H