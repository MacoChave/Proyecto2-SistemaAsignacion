#include "edificio.h"
#pragma warning(disable:4996)

NodoEdificio::NodoEdificio(char *nombre_)
{
	nombre = new char[strlen(nombre_) + 1];
	strcpy(nombre, nombre_);
	salones = new Salon();
	anterior = NULL;
	siguiente = NULL;
}

NodoEdificio::~NodoEdificio()
{
	delete[](nombre);
	delete(salones);
	anterior = NULL;
	siguiente = NULL;
}

Edificio::Edificio()
{
	primero = NULL;
	ultimo = NULL;
}

Edificio::~Edificio()
{
	primero = NULL;
	ultimo = NULL;
}

void Edificio::add(char *nombre)
{
	if (primero != NULL)
		add(primero->siguiente, nombre);
	else
	{
		primero = new NodoEdificio(nombre);
		primero->anterior = primero;
		primero->siguiente = primero;
		ultimo = primero;
	}
}

void Edificio::add(NodoEdificio *actual, char *nombre)
{
	if (actual != NULL)
	{
		if (strcmp(primero->nombre, nombre) > 0)
		{
			NodoEdificio *nuevo = new NodoEdificio(nombre);
			nuevo->siguiente = primero;
			nuevo->anterior = ultimo;
			primero->anterior = nuevo;
			ultimo->siguiente = nuevo;
		}
		else if (strcmp(ultimo->nombre, nombre) < 0)
		{
			NodoEdificio *nuevo = new NodoEdificio(nombre);
			nuevo->siguiente = primero;
			nuevo->anterior = ultimo;
			primero->anterior = nuevo;
			ultimo->siguiente = nuevo;
			ultimo = nuevo;
		}
		else
		{
			if (strcmp(actual->nombre, nombre) > 0)
			{
				NodoEdificio *nuevo = new NodoEdificio(nombre);
				nuevo->siguiente = actual;
				nuevo->anterior = actual->anterior;
				actual->anterior->siguiente = nuevo;
				actual->anterior = nuevo;
			}
			else if (strcmp(actual->nombre, nombre) < 0)
				add(actual->siguiente, nombre);
		}
	}
}

void Edificio::addSalon(char *nombre, int numero, int capacidad)
{
	NodoEdificio *temp = getNodoEdificio(nombre);

	if (temp != NULL)
		temp->salones->add(numero, capacidad);
}

void Edificio::remove(char *nombre)
{
	if (primero != NULL)
		remove(primero, nombre);
}

void Edificio::remove(NodoEdificio *actual, char *nombre)
{
	if (actual != NULL)
	{
		if (strcmp(primero->nombre, nombre) == 0)
		{
			NodoEdificio *temp = primero;
			primero = temp->siguiente;
			ultimo->siguiente = primero;
			primero->anterior = ultimo;

			delete(temp);
		}
		else if (strcmp(ultimo->nombre, nombre) == 0)
		{
			NodoEdificio *temp = ultimo;
			ultimo = temp->anterior;
			ultimo->siguiente = primero;
			primero->anterior = ultimo;

			delete(temp);
		}
		else
		{
			if (strcmp(actual->nombre, nombre) < 0)
			{
				if (actual->siguiente != primero)
					remove(actual->siguiente, nombre);
			}
			else if (strcmp(actual->nombre, nombre) == 0)
			{
				actual->anterior->siguiente = actual->siguiente;
				actual->siguiente->anterior = actual->anterior;

				delete(actual);
			}
		}
	}
}

void Edificio::removeSalon(char *nombre, int salon)
{
	if (primero != NULL)
		removeSalon(primero, nombre, salon);
}

void Edificio::removeSalon(NodoEdificio *actual, char *nombre, int salon)
{
	if (actual != NULL)
	{
		if (strcmp(primero->nombre, nombre) == 0)
		{
			primero->salones->remove(salon);

			/*NodoEdificio *temp = primero;
			primero = temp->siguiente;
			ultimo->siguiente = primero;
			primero->anterior = ultimo;

			delete(temp);*/
		}
		else if (strcmp(ultimo->nombre, nombre) == 0)
		{
			ultimo->salones->remove(salon);

			/*NodoEdificio *temp = ultimo;
			ultimo = temp->anterior;
			ultimo->siguiente = primero;
			primero->anterior = ultimo;

			delete(temp);*/
		}
		else
		{
			if (strcmp(actual->nombre, nombre) < 0)
			{
				if (actual->siguiente != primero)
					remove(actual->siguiente, nombre);
			}
			else if (strcmp(actual->nombre, nombre) == 0)
			{
				actual->salones->remove(salon);

				/*actual->anterior->siguiente = actual->siguiente;
				actual->siguiente->anterior = actual->anterior;

				delete(actual);*/
			}
		}
	}
}

NodoEdificio* Edificio::getNodoEdificio(char *nombre)
{
	return getNodoEdificio(primero, nombre);
}

NodoEdificio* Edificio::getNodoEdificio(NodoEdificio *actual, char *nombre)
{
	if (actual != NULL)
	{
		if (strcmp(actual->nombre, nombre) == 0)
			return actual;
		else if (strcmp(actual->nombre, nombre) < 0)
			return getNodoEdificio(actual->siguiente, nombre);
		else
			return NULL;
	}
	else
		return NULL;
}

void Edificio::escribir(char filename[], char texto[], char *modo)
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

void Edificio::graph()
{
	char dot[128];
	strcpy(dot, "digraph edificio {\n");
	strcat(dot, "\tnodesep=.05;\n");
	strcat(dot, "\tnode [shape=record,width=1.5,height=.5];\n");

	escribir("edificio.dot", dot, "w");

	graph(primero);

	graphSalones(primero);

	strcpy(dot, "\"\"");

	strcat(dot, "}");

	escribir("edificio.dot", dot, "a");

	system("dot -Tpng edificio.dot -o edificio.png");
}

void Edificio::graph(NodoEdificio *actual)
{
	if (actual != NULL)
	{
		char dot[128];
		strcpy(dot, "\n");
		strcat(dot, actual->toGraph());
		strcat(dot, "[label = \"");
		strcat(dot, actual->toString());
		strcat(dot, "\"];");
		strcat(dot, "\n");
		if (actual->siguiente != primero)
		{
			strcat(dot, actual->toGraph());
			strcat(dot, " -> ");
			strcat(dot, actual->siguiente->toGraph());
			strcat(dot, ";\n");
		}
		escribir("edificio.dot", dot, "a");

		if (actual->siguiente != primero)
			graph(actual->siguiente);
	}
}

char* NodoEdificio::toGraph()
{
	char temp[10];
	strcpy(temp, "ED");
	strcat(temp, nombre);

	return temp;
}

char* NodoEdificio::toString()
{
	return nombre;
}

void Edificio::graphSalones(NodoEdificio *actual)
{
	if (actual != NULL)
	{
		char dot[100];
		strcpy(dot, "\n");
		strcat(dot, actual->toGraph());
		strcat(dot, " -> ");
		if (actual->salones != NULL)
		{
			escribir("edificio.dot", dot, "a");

			actual->salones->graph();
		}

		if (actual->siguiente != primero)
			graphSalones(actual->siguiente);
	}
}