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
	//GraphNode<T>* last;
	int size = 64;
	GraphList<T>();
	~GraphList<T>();

	void push_at(int index, int index2, GraphNode<T>* value);
	GraphNode<T>* return_at_array(int index, int index2);
	GraphNode<T>* return_at_index(int index, GraphNode<T>* root);
	GraphNode<T>* detectMouse(Vector2 mouse, bool pressed);
	GraphNode<T>* detectMouse(GraphNode<T>* root, Vector2 mousePos, bool pressed);
	GraphNode<T>* searchNode(GraphNode<T>* first, GraphNode<T>* node);
	void renderNode(GraphNode<T>* node);
	void swap(GraphNode<T>* ghLeft, GraphNode<T>* ghRight);
	GraphNode<T>* graphArr[8][8];
};

template<class T>
inline GraphList<T>::GraphList()
{
	try
	{
		first = nullptr;

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
				//printf("Node found at: %i\nWith path: %s", index, it->value->textText.c_str());
				return it;
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
			it = it->next;
		}
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
			   && mousePos.y >= it->value->rect->y && mousePos.y <= it->value->rect->y + it->value->rect->h && pressed)
			{
				printf("Mouse on: %s\n", it->value->textText.c_str());
				return it;
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
			it = it->next;
		}

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
		GraphNode<T>* it = first;
		GraphNode<T>* it2 = nullptr;
		if(first->bottom != nullptr)
			it2 = first->bottom;
		while(it != nullptr)
		{
			if(it == node)
				return it;

			if(it->next == nullptr)
			{
				if(it2 != nullptr)
					searchNode(it2, node);
			}
			it = it->next;

		}
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


template<class T>
inline void GraphList<T>::swap(GraphNode<T>* ghLeft, GraphNode<T>* ghRight)
{
	try
	{
		GraphNode<T>* firstNode = searchNode(first, ghLeft);
		GraphNode<T>* secondNode = searchNode(first, ghRight);
		if(firstNode->value->ID == secondNode->value->ID &&ghLeft != nullptr)
		{
			printf("Son igualeeeeees!\n");
			cout << ghLeft->value->textText.c_str()<< endl <<  ghRight->value->textText.c_str() << endl;
		}
		else if(searchNode(first, ghLeft)->value->ID != ghRight->value->ID && ghLeft != nullptr)
		{
			 printf("No son igualeeese!\n");
			 cout << ghLeft->value->textText.c_str() << endl << ghRight->value->textText.c_str() << endl;

		} else
			cout << "Que esta pasando!\n";

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{
		cout << "Ups! Something crashed!\n";
	}
}

#endif // ! GRAPHLIST_H