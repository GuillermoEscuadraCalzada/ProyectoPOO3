#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>
#include <sstream>
using std::cout; using std::exception; using std::endl; using std::to_string; using std::string;

template<class T>
class Vector
{
public:
	Vector<T>();

	~Vector<T>();

	void push_back_texture(T key, SDL_Texture* value);
	void push_back_text_texture(T key, SDL_Texture* value);
	T* at(T key);

	SDL_Texture* returnTexture(T key);
	SDL_Texture* returnText(T key);
	void pop_back();
	void print();
	void destroyTextures();

	int getCurrent()
	{
		return current;
	}

	int getSize()
	{
		return size;
	}


	SDL_Texture** textureArray;
	T** textureKeyArr;

private:
	int size;
	int current;
	T lastKey;
};


template<class T>
inline Vector<T>::Vector()
{
	try
	{
		this->size = 1;
		this->current = 0;

		textureArray = new SDL_Texture * [size];

		textureKeyArr = new T * [size];
		
		for(int i = 0; i < size; i++)
		{
			textureArray[i] = nullptr;
			textureKeyArr[i] = nullptr;
		}

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}


template<class T>
inline Vector<T>::~Vector()
{
	try
	{
		delete textureKeyArr;	
		delete textureArray;

		size = NULL;
		current = NULL;
		textureKeyArr = NULL;
		textureArray = nullptr;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	}catch(...)
	{

	}
}

template<class T>
inline void Vector<T>::push_back_texture(T key, SDL_Texture* value)
{
	try
	{
		
		SDL_Texture* temp = value;
		T* temp2 = new T(key);
		if(current == size)
		{
			size *= 2;
			SDL_Texture** newArr = new SDL_Texture * [size];
			T** newKA = new T * [size];
			for(int i = 0; i < size; i++)
			{
				newArr[i] = nullptr;
				newKA[i] = NULL;
			}

			for(int i = 0; i < size / 2; i++)
			{
				newArr[i] = textureArray[i];
				newKA[i] = textureKeyArr[i];
			}

			delete textureArray;
			delete textureKeyArr;

			textureArray = newArr;
			textureKeyArr = newKA;
		}
		if(textureKeyArr[current] == NULL)
		{
			textureKeyArr[current] = temp2;
			textureArray[current] = temp;
			current++;
			return;
		}
		else if(textureKeyArr[current] != NULL)
		{
			cout << "Can't push this item, it already exists\n";
		}


	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}

/*Esta función te regresará un objeto de tipo SDL_Texture, el cual se buscará por medio de la llave (dirección de archivo)
	@param[ key ] llave que identificará al objeto
	@return	un objeto de tipo SDL_Texture*/
template<class T>
inline SDL_Texture* Vector<T>::returnTexture(T key)
{
	try
	{
		/*Busca hasta llegar a current*/
		for(int i = 0; i <= current; i++)
		{	
			//Si este elemento es igual a nulo, regresa nulo
			if(textureKeyArr[i] == nullptr)
			{
				return nullptr;
			} else
			{	//En caso contrario, regresa el objeto del arreglo objArray
				if(*textureKeyArr[i] == key)
				{
					return textureArray[i];
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

/*Utiliza la función de SDL para destruir las texturas*/
template<class T>
void Vector<T>::destroyTextures()
{
	try
	{
		/*Busca por el arreglo hasta encontrar con un objeto de tipo SDL_Texture*/
		for(int i = 0; i < current; i++)
		{
			
			if(textureArray[i] != nullptr)
			{
				SDL_DestroyTexture(textureArray[i]);
			}
		}
	} catch(const std::exception& e)
	{

	}
}

template<class T>
inline void Vector<T>::pop_back()
{

	try
	{

	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}

/*Imprime las direcciones de las texturas o de algun otro elemento*/
template<class T>
inline void Vector<T>::print()
{
	try
	{
		cout << "Indice\t\tKey\t\t\t\tObject\n";
		//Se cicla desde el inicio hasta current, porque desde current hasta el final del vector, no hay elementos.	
		for(int i = 0; i < size; i++)
		{
			//Si el arreglo en esta posición es diferente de nulo, imprime su identificador.
			if(textureArray[i] != nullptr)
			{
				
				cout << "Index: " << to_string(i) + "\t" << *textureKeyArr[i];
			}
			//Si es igual a nulo, imprime el índice y di que está vacío
			else
				cout << to_string(i) + "\tEmpty\tEmpty\n";

		}
		cout << endl;
	} catch(exception & e)
	{
		cout << "Exception caught: " << e.what() << endl;
	} catch(...)
	{

	}
}





#endif // !VECTOR_H


