#include "salon.h"
#pragma warning(disable:4996)

NodoSalon::NodoSalon(int numero_, int capacidad_)
{
	numero = numero_;
	capacidad = capacidad_;
	siguiente = NULL;
}

NodoSalon::~NodoSalon()
{
	numero = 0;
	capacidad = 0;
	siguiente = NULL;
}

Salon::Salon()
{
	primero = NULL;
	ultimo = NULL;
}

Salon::~Salon()
{
	primero = NULL;
	ultimo = NULL;
}

void Salon::add(int numero, int capacidad)
{
	if (primero != NULL)
		add(primero, numero, capacidad);
	else
	{
		primero = new NodoSalon(numero, capacidad);
		ultimo = primero;
	}
}

void Salon::add(NodoSalon *actual, int numero, int capacidad)
{
	if (actual != NULL)
	{
		if (primero->numero > numero)
		{
			NodoSalon *nuevo = new NodoSalon(numero, capacidad);
			nuevo->siguiente = primero;
			primero = nuevo;
		}
		else if (ultimo->numero < numero)
		{
			NodoSalon *nuevo = new NodoSalon(numero, capacidad);
			ultimo->siguiente = nuevo;
			ultimo = nuevo;
		}
		else
		{
			if (actual->siguiente->numero > numero)
			{
				NodoSalon *nuevo = new NodoSalon(numero, capacidad);
				nuevo->siguiente = actual->siguiente;
				actual->siguiente = nuevo;
			}
			else if (actual->siguiente->numero < numero)
			{
				add(actual->siguiente, numero, capacidad);
			}
		}
	}
}

void Salon::remove(int numero)
{

}

void Salon::remove(NodoSalon *actual, int numero, int capacidad)
{

}

void Salon::escribir(char filename[], char texto[], char *modo)
{
	char path[25];
	strcpy(path, filename);

	FILE *archivo;
	archivo = fopen(path, modo);

	if (!feof(archivo))
	{
		fprintf(archivo, "%s", texto);
		fflush(archivo);
		fclose(archivo);
	}
}

void Salon::graph()
{
	graph(primero);
}

void Salon::graph(NodoSalon *actual)
{
	if (actual != NULL)
	{
		char dot[50];
		strcat(dot, actual->toGraph());
		strcat(dot, ";\n");
		strcat(dot, actual->toGraph());
		strcat(dot, "[label = \"");
		strcat(dot, actual->toString());
		strcat(dot, "\"];");
		strcat(dot, "\n");
		if (actual->siguiente != NULL)
		{
			strcat(dot, actual->toGraph());
			strcat(dot, " -> ");

			escribir("edificio.dot", dot, "a");
		}

		if (actual->siguiente != NULL)
			graph(actual->siguiente);
	}
}

char* NodoSalon::toGraph()
{
	char nodo[8];
	sprintf(nodo, "SL%d", numero);

	return nodo;
}

char* NodoSalon::toString()
{
	char nodo[10];
	sprintf(nodo, "%d\\n%d", numero, capacidad);

	return nodo;
}