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
	
	GraphNode<T>* next;	//Apuntador al siguiente elemento dentro del grafo
	GraphNode<T>* prev;	//Apuntador al elemento anterior dentro del grafo
	GraphNode<T>* top;	//Apuntador a una posición superior dentro del grafo
	GraphNode<T>* bottom;	//Apuntador que busca la posición inferior de este nodo

	/*Constructor de la clase nodo
		@param[T value] cualquier elemento que se añade a esta lista y se lo iguala al valor de la clase*/

	GraphNode<T>(T _value, Vector2 vec) : value(_value), position(vec)
	{
		visited = false;	//Visited empieza en falso
		index = 0;	//Indice es igual a cero
		next = prev = top = bottom = nullptr;
	};
	
	GraphNode<T>() {};
};



template<class T>
class GraphList
{
public:

	GraphNode<T>* first;
	GraphNode<T>* nodeToFind;

	//GraphNode<T>* last;
	int size = 64;
	GraphList<T>();
	~GraphList<T>();
	bool found = false;

	void push_at(int index, int index2, GraphNode<T>* value);
	GraphNode<T>* return_at_array(int index, int index2);
	GraphNode<T>* return_at_index(int index, GraphNode<T>* root);
	GraphNode<T>* detectMouse(Vector2 mouse, bool pressed);
	GraphNode<T>* detectMouse(GraphNode<T>* root, Vector2 mousePos, bool pressed);
	GraphNode<T>* searchNode(GraphNode<T>* first, GraphNode<T>* node);
	void renderNode(GraphNode<T>* node);
	void swap(GraphNode<T>* ghLeft, GraphNode<T>* ghRight);
	GraphNode<T>* graphArr[8][8];
private:
	int index1;
	int index2;
};

template<class T>
inline GraphList<T>::GraphList()
{
	try
	{
		first = nullptr;
		nodeToFind = nullptr;
		index1 = index2 = NULL;
	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	}
	catch(...)
	{
		cout << "Ups, something crashed!\n";
	}

}

/*Destructor de la clase grafo*/
template<class T>
inline GraphList<T>::~GraphList()
{
	try
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				graphArr[i][j] = nullptr;
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

/*Push at timará dos índices que le ayudarán a ingresar un nodo a su arreglo de nodos
 *@param[int index] indice de las filas del arreglo [index][]
 *@param[int index2] indice de las columnas del arreglo [index][index2]
 *@param[GraphNode* value] nodo que entrará al arreglo en los índices establecidos*/
template<class T>
inline void GraphList<T>::push_at(int index, int index2, GraphNode<T>* value)
{
	try{	
		bool placed = false;	//Booleano que hará un break en el primer for, así se evita buscar en todas las posiciones
		GraphNode<T>* temp = value;//un nodo temporal que es igual al valor
		
		//Ciclo entre el arreglo de los nodos
		for(int i = 0; i < size;i++ )
		{
			for(int j = 0; j < size; j++)
			{
				graphArr[index][index2] = temp; //En esta posición del arreglo, se guardará el valor
				placed = true; //Se vuelve verdader
				break; //Deja de avanzar
			}
			//Si es verdadero, deja de avanzar
			if(placed)
				break;
		}
	} catch(exception & e)
	{
		cout << "Exception caght: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups, something crashed!\n";
	}
}

/*Esta función nos regresa un nodo en el arreglo de nodos gracias a los índices indicados en los parámetros
 *param[int index] indice en las filas del arreglo
 *param[int index2] indice en las columnas del arreglo
 *return el nodo en esa posición 
 */
template<class T>
inline GraphNode<T>* GraphList<T>::return_at_array(int index, int index2)
{
	try
	{
		/*Se recorre todo el arreglo hasta encontrar la posición de los índices dentro del arreglo*/
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				//Si 'i' y 'j' son iguales, regresa este nodo
				if(i == index && j == index2)
				{
					return graphArr[i][j];	//Regresa este nodo
				}
			}
		}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
	
	}
}

/*Esta función avanzará por todos los nodos hasta encontrar con el nodo indicado y así poder hallar el indicado
 *@param[int index] indice que se debe buscar entre los nodos
 *@param[GraphNode<T>* root] apuntador que nos servirá para ir por medio de la recursividad entre ndoos.*/
template<class T>
inline GraphNode<T>* GraphList<T>::return_at_index(int index, GraphNode<T>* root)
{
	try
	{
		GraphNode<T>* it = root;	//Nodo iterador que es igual a root
		GraphNode<T>* it2 = nullptr;	//Segundo nodo iterador iniciado en nulo

		//Si el apuntador debajo de la raíz es diferente a nulo, el segundo iterador avanza ahí mismo
		if(root->bottom != nullptr)
			it2 = root->bottom;

		//Si index es mayor al último índice o si el índice es menor a cero, regresa nulo, esta fuera de los límites
		if(index > size - 1 || index < 0)
			return nullptr;
		
		/*Avanza el primer iterador hasta encontrar el resultado*/
		while(it != nullptr)
		{
			//Si el iterador tiene el índice igual al introducido, regresa este valor
			if( it->index == index)
			{
				nodeToFind = it;
				found = true;
			}
			//Si su siguiente nodo es nulo, avanza al nodo inferior al nodo principal de esta línea
			if(it->next == nullptr)
			{
				//Si ese iterador es diferente de nulo, avanza
				if(it2 != nullptr)
				{
					return_at_index(index, it2); //Avanza al nodo inferior del primer nodo de esta fila	
				}
			}
			if(found)
				break;
			it = it->next;
		}
		found = false;
		return nodeToFind;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}

/*Esta función detecta si las posiciones del mouse se encuentran dentro de las casillas de cada nodo, además, te regrsesa el apuntador a ese nodo
 *@param[Vector2] el vector donde se almacena la información del mouse
 *@param[bool pressed] booleano para controlar información
 *@return te regresa un nodo*/
template<class T>
inline GraphNode<T>* GraphList<T>::detectMouse(Vector2 mouse, bool pressed)
{
	try
	{
		std::string str;
		bool selected = false;
	
		for(int i = 0; i < 8; i++)
		{

			for(int j = 0; j < 8; j++)
			{
				SDL_Rect *rect = graphArr[i][j]->value->rect;			
				if(mouse.x >= rect->x && mouse.x <= rect->x + rect->w && mouse.y >= rect->y && mouse.y <= rect->y + rect->h )
				{
					selected = true;
					return graphArr[i][j];
					break;
				}
			}
			if(selected)
				break;
			
		}
	} catch(exception & e){
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}

/*Esta función detecta si el mouse se encuentra en la ubicación del nodo correspondiente a la posición del mouse
 *@param[GraphNode<T>*] Nodo principal desde donde comenzará la búsqueda
 *@param[Vector2] vector que nos indica la posición del mouse
 *@param[bool] este booleano proviene del InputManager y pregunta si algun botón del mouse fue presionado
 *@return nodo de la clase Lista.*/
template<class T>
inline GraphNode<T>* GraphList<T>::detectMouse(GraphNode<T>* root, Vector2 mousePos, bool pressed)
{
	try
	{
		GraphNode<T>* it = root;	//Nodo que es igual a la raíz desde donde partirá
		GraphNode<T>* it2 = nullptr;	//Ese nodo comienza en nulo

		//Si el apuntador debajo de la raíz es diferente a nulo, el segundo iterador avanza ahí mismo
		if(root->bottom != nullptr)
			it2 = root->bottom;

		/*Avanza el primer iterador hasta encontrar el resultado*/
		while(it != nullptr)
		{
			//Pregunta si la posición del mouse se encuentra entre el cuadrante de la imagen y regresa su valor
			if(mousePos.x >= it->value->rect->x && mousePos.x <= it->value->rect->x + it->value->rect->w
			   && mousePos.y >= it->value->rect->y && mousePos.y <= it->value->rect->y + it->value->rect->h)
			{
				if(pressed)
				{
					nodeToFind = it;	 //Este nodo guarda el valor del iterador.
					nodeToFind->value->rect->w *= 0.5;	//Se multiplica el ancho por la mitad
					nodeToFind->value->rect->h *= 0.5;	//Se multiplica lo alto por la mitad

					/*La imagen se mueve hacia adelante la mitad de su anchura actual y hacia abajo la mitad de su altura actual para quedar en el centro del cuadrante*/
					nodeToFind->value->Position(Vector2(nodeToFind->value->Position().x + nodeToFind->value->rect->w / 2, 
														nodeToFind->value->Position().y + nodeToFind->value->rect->h / 2));

					found = true;	//Este booleano se vuelve verdadero
				}
			}

			//Si su siguiente nodo es nulo, avanza al nodo inferior al nodo principal de esta línea
			if(it->next == nullptr)
			{
				//Si ese iterador es diferente de nulo, avanza
				if(it2 != nullptr)
				{
					detectMouse(it2, mousePos, pressed);
				}
			}
			//Si es verdadero, detente
			if(found)
				break;
			
			it = it->next;
		}
		found = false;
		return nodeToFind;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

/*Se busca un nodo dentro de todos los nodos del grafo
 *@param[GraphNode<T>* first] nodo desde el cual se empezará a buscar en la fila
 *@param[GraphNode<T>* node] nodo que se desea encontrar*/
template<class T>
inline GraphNode<T>* GraphList<T>::searchNode(GraphNode<T>* first, GraphNode<T>* node)
{
	try
	{
		GraphNode<T>* it = first;	//Nodo que se igualará al primer nodo del argumento, 
		GraphNode<T>* it2 = nullptr;	//Un nodo que es nulo 

		//Si el nodo inferior al nodo del argumento es diferente de nulo, el nodo it2 será igual a ese valor
		if(first->bottom != nullptr)
			it2 = first->bottom;


		//Itera por todo el grafo
		while(it != nullptr)
		{

			//Si encuentras el nodo
			if(it == node)
			{
				nodeToFind = it;	//NodeToFind es igual al iterador
				found = true;	//Regresa verdadero
			}
			//Si el siguiente del iterador es igual a nulo, 
			if(it->next == nullptr)
			{
				//Y mientras it2 no sea nulo,
				if(it2 != nullptr)
					searchNode(it2, node); //Avanza al iterador it2
			}
			//Si se encontró el nodo, ya no avances más
			if(found)
				break;
			it = it->next; //Avanza al siguiente

		}
		found = false;	//Found se vuelve falso
		return nodeToFind; //Regresa NodeToFind
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

/*Esta función nos permite renderizar cualquier imagen dentro de los nodos en el arreglo de manera recursiva,
 *guardos una variable del siguiente al que apunta el nodo principal y cada vez que ese sea nulo, avanzamos al que se encuentra en la parte
 *inferior al nodo principal
 *@param[node] nodo que irá recorriendo la función*/
template<class T>
inline void GraphList<T>::renderNode(GraphNode<T>* node)
{
	try
	{

		GraphNode<T>* it = node;	//Un iterador al nodo del argumento
		GraphNode<T>* it2 = nullptr; //Un iterador que comienza nulo
		if(node->bottom != nullptr) //Si el nodo que se encuentra debajo del nodo principal es diferente de nulo, el nodo it2 avanza a ese nodo
		{
			it2 = node->bottom;
		}

		//Avanza hasta que este sea nulo
		while(it != nullptr)
		{
			//Si esete iterador no es nulo, renderizalo
			if(it != nullptr)
			{
				it->value->Render();
			}
			//Si su siguiente nodo es nulo, avanza al nodo inferior al nodo principal de esta línea
			if(it->next == nullptr)
			{
				//Si ese iterador es diferente de nulo, avanza
				if(it2 != nullptr)
				{
					renderNode(it2);
				}
			}
			it = it->next;	//Avanza al siguiente para finalizar
		}
		////Se cicla en todo el arreglo 
		//for(int i = 0; i < 8; i++)
		//{
		//	for(int j = 0; j < 8; j++)
		//	{
		//		graphArr[i][j]->value->Render(); //Se renderiza cada nodo
		//	}
		//}
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! It crashed!\n";
	}
}

/*Esta función intercambiará las texturas de los nodos seleccionados con el mouse
 *@param[GraphNode<T>* ghleft] primer nodo tocado en el juego
 *@param[GraphNode<T>* ghRight] segundo nodo tocado en el juego*/
template<class T>
inline void GraphList<T>::swap(GraphNode<T>* ghLeft, GraphNode<T>* ghRight)
{
	try
	{

		GraphNode<T>* firstNode = searchNode(first, ghLeft);	//Busca el nodo en el grafo y guardalo dentro de una variable
		GraphNode<T>* secondNode = searchNode(first, ghRight); //Busca el nodo en el grafo y fuardalo dentro de una variable
		T text1 = firstNode->value;	//Crea una variable tipo template e igualala al valor dentro de firstNode
		T text2 = secondNode->value;	//Crea una variable tipo template e igualala al valor dentro de secondNode

		//Preguntar si el segundo nodo es algún hijo del primer nodo, si lo es, crea un vector temporal
		if(secondNode == firstNode->next || secondNode == firstNode->prev || secondNode == firstNode->top || secondNode == firstNode->bottom)
		{
			Vector2 temp = text1->Position();	//Vector temporal de la posición de text1
			text1->Position(text2->Position()); //Text 1 cambia su posición al de text2
			text2->Position(temp); //Text2 toma el valor del vector temporal
			text1->Position(Vector2(text1->Position().x - text1->rect->w / 2, text1->Position().y - text1->rect->h / 2));	//Regresa la posición de text1 a al inicio del cuadrante
			text1->rect->w *= 2;	//Duplica su anchura actual
			text1->rect->h *= 2;	//Duplica su altura actual

			text2->Position(Vector2(text2->Position().x - text2->rect->w / 2, text2->Position().y - text2->rect->h / 2)); //Regresa la posición de text2 a al inicio del cuadrante
			text2->rect->w *= 2;	//Duplica su anchura actual
			text2->rect->h *= 2;	//Duplica su altura actual
			firstNode->value = text2;	//El valor del primer nodo cambia
			secondNode->value = text1;	//Al igual que el valor del segundo nodo
			
		}
		else
		{
			printf("Te conozco?\n");
		}


	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

#endif // ! GRAPHLIST_H