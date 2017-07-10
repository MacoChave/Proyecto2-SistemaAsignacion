#include "usuarios.h"
#pragma warning(disable:4996)

NodoUsuario::NodoUsuario(char *nombre_, char *pass_, char *tipo_)
{
	nombre = new char[strlen(nombre_) + 1];
	strcpy(nombre, nombre_);
	pass = new char[strlen(pass_) + 1];
	strcpy(pass, pass_);
	tipo = new char[strlen(tipo_) + 1];
	strcpy(tipo, tipo_);
	siguiente = NULL;
	anterior = NULL;
}

NodoUsuario::~NodoUsuario()
{
	delete[](nombre);
	delete[](pass);
	delete[](tipo);
	siguiente = NULL;
	anterior = NULL;
}

Usuario::Usuario()
{
	primero = NULL;
	ultimo = NULL;
}

Usuario::~Usuario()
{
	primero = NULL;
	ultimo = NULL;
}

void Usuario::add(char *nombre, char *pass, char *tipo)
{
	if (primero != NULL)
		add(primero, nombre, pass, tipo);
	else
	{
		primero = new NodoUsuario(nombre, pass, tipo);
		ultimo = primero;
	}
}

void Usuario::add(NodoUsuario *actual, char *nombre, char *pass, char *tipo)
{
	if (actual != NULL)
	{
		if (strcmp(primero->nombre, nombre) > 0)
		{
			NodoUsuario *nuevo = new NodoUsuario(nombre, pass, tipo);
			nuevo->siguiente = primero;
			primero->anterior = nuevo;
			primero = nuevo;
		}
		else if (strcmp(ultimo->nombre, nombre) < 0)
		{
			NodoUsuario *nuevo = new NodoUsuario(nombre, pass, tipo);
			ultimo->siguiente = nuevo;
			nuevo->anterior = ultimo;
			ultimo = nuevo;
		}
		else
		{
			if (strcmp(actual->nombre, nombre) > 0)
			{
				NodoUsuario *nuevo = new NodoUsuario(nombre, pass, tipo);
				nuevo->siguiente = actual;
				nuevo->anterior = actual->anterior;
				actual->anterior->siguiente = nuevo;
				actual->anterior = nuevo;
			}
			else if (strcmp(actual->nombre, nombre) < 0)
			{
				add(actual->siguiente, nombre, pass, tipo);
			}
		}
	}
}

void Usuario::remove(char *nombre)
{

}

void Usuario::remove(NodoUsuario *actual, char *nombre)
{

}

char* Usuario::check(char *nombre, char *pass)
{
	if (primero != NULL)
	{
		if (strcmp(primero->nombre, nombre) == 0 && strcmp(primero->pass, pass) == 0)
			return primero->tipo;
		else if (strcmp(ultimo->nombre, nombre) == 0 && strcmp(ultimo->pass, pass) == 0)
			return ultimo->tipo;
		else
			return check(primero->siguiente, nombre, pass);
	}
	else
		return "x";
}

char* Usuario::check(NodoUsuario *actual, char *nombre, char *pass)
{
	if (strcmp(actual->nombre, nombre) == 0 && strcmp(actual->pass, pass) == 0)
		return actual->tipo;
	else if (strcmp(actual->nombre, nombre) < 0 && strcmp(actual->pass, pass) < 0)
		return check(actual->siguiente, nombre, pass);
	else
		return "x";
}

void Usuario::escribir(char filename[], char texto[], char *modo)
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

void Usuario::graph()
{
	char dot[100];
	strcpy(dot, "digraph usuarios {\n");
	strcat(dot, "\tnodesep=.05;\n");
	strcat(dot, "\trankdir=LR\n");
	strcat(dot, "\tnode [shape=record,width=1.5,height=.5];\n");

	escribir("usuario.dot", dot, "w");
	strcpy(dot, "");
	
	graph(primero);

	strcpy(dot, "}");

	escribir("usuario.dot", dot, "a");

	system("dot -Tpng usuario.dot -o usuario.png");
}

void Usuario::graph(NodoUsuario *actual)
{
	if (actual != NULL)
	{
		char dot[100];
		strcpy(dot, "\n");
		strcat(dot, actual->toGraph());
		strcat(dot, "[label = \"");
		strcat(dot, actual->toString());
		strcat(dot, "\"];");
		strcat(dot, "\n");
		if (actual->siguiente != NULL)
		{
			strcat(dot, actual->toGraph());
			strcat(dot, " -> ");
			strcat(dot, actual->siguiente->toGraph());
			strcat(dot, ";\n");
		}
		escribir("usuario.dot", dot, "a");

		if (actual->siguiente != NULL)
			graph(actual->siguiente);
	}
}

char* NodoUsuario::toGraph()
{
	char nodo[20];
	sprintf(nodo, "US%s", nombre);

	return nodo;
}

char* NodoUsuario::toString()
{
	char nodo[50];
	sprintf(nodo, "%s\\n", nombre);
	strcat(nodo, tipo);
	return nodo;
}