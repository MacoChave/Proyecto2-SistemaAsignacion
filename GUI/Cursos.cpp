#include "Cursos.h"
#pragma warning(disable:4996)

NodoCurso::NodoCurso(int codigo_, char *nombre_, int semestre_, int noCreditos_)
{
	codigo = codigo_;
	nombre = new char[strlen(nombre_) + 1];
	strcpy(nombre, nombre_);
	semestre = semestre_;
	noCreditos = noCreditos_;
	siguiente = NULL;
}

NodoCurso::~NodoCurso()
{
	codigo = 0;
	delete[](nombre);
	semestre = 0;
	noCreditos = 0;
	siguiente = NULL;
}

Curso::Curso()
{
	primero = NULL;
	ultimo = NULL;
}

Curso::~Curso()
{
	primero = NULL;
	ultimo = NULL;
}

void Curso::add(int codigo, char *nombre, int semestre, int noCreditos)
{
	if (primero != NULL)
		add(primero, codigo, nombre, semestre, noCreditos);
	else
	{
		primero = new NodoCurso(codigo, nombre, semestre, noCreditos);
		ultimo = primero;
	}
}

void Curso::add(NodoCurso *actual, int codigo, char *nombre, int semestre, int noCreditos)
{
	if (actual != NULL)
	{
		if (primero->codigo > codigo)
		{
			NodoCurso *nuevo = new NodoCurso(codigo, nombre, semestre, noCreditos);
			nuevo->siguiente = primero;
			primero = nuevo;
		}
		else if (ultimo->codigo < codigo)
		{
			NodoCurso *nuevo = new NodoCurso(codigo, nombre, semestre, noCreditos);
			ultimo->siguiente = nuevo;
			ultimo = nuevo;
		}
		else
		{
			if (actual->siguiente->codigo > codigo)
			{
				NodoCurso *nuevo = new NodoCurso(codigo, nombre, semestre, noCreditos);
				nuevo->siguiente = actual->siguiente;
				actual->siguiente = nuevo;
			}
			else if (actual->siguiente->codigo < codigo)
				add(actual->siguiente, codigo, nombre, semestre, noCreditos);
		}
	}
}

void Curso::remove(int codigo)
{
	if (primero != NULL)
		remove(primero, codigo);
}

void Curso::remove(NodoCurso *actual, int codigo)
{
	if (actual != NULL)
	{
		if (primero->codigo == codigo)
		{
			NodoCurso *temp = primero;
			if (primero == ultimo)
			{
				ultimo = NULL;
				primero = NULL;
			}
			else
				primero = primero->siguiente;

			delete(temp);
			temp = NULL;
		}
		else
		{
			if (actual->siguiente->codigo == codigo)
			{
				NodoCurso *temp = actual->siguiente;
				actual->siguiente = temp->siguiente;

				delete(temp);
				temp = NULL;
			}
			else if (actual->siguiente->codigo < codigo)
				remove(actual->siguiente, codigo);
		}
	}
}

void Curso::editar(int codigo_, char *nombre_, int semestre_, int noCreditos_)
{
	NodoCurso *temp = buscar(codigo_);
	if (temp != NULL)
	{
		strcpy(temp->nombre, nombre_);
		temp->semestre = semestre_;
		temp->noCreditos = noCreditos_;
	}
}

NodoCurso* Curso::buscar(int codigo_)
{
	NodoCurso *temp = primero;

	while (temp != NULL)
	{
		if (temp->codigo < codigo_)
			temp = temp->siguiente;
	}
	if (temp != NULL && temp->codigo == codigo_)
		return temp;
	else
		return NULL;
}

void Curso::escribir(char filename[], char texto[], char *modo)
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

void Curso::graph()
{
	char dot[128];
	strcpy(dot, "digraph cursos {\n");
	strcat(dot, "\tnodesep=.05;\n");
	strcat(dot, "rankdir=LR");
	strcat(dot, "\tnode [shape=record,width=1.5,height=.5];\n");

	escribir("curso.dot", dot, "w");

	graph(primero);

	strcpy(dot, "}");

	escribir("curso.dot", dot, "a");

	system("dot -Tpng curso.dot -o curso.png");
}

void Curso::graph(NodoCurso *actual)
{
	if (actual != NULL)
	{
		char dot[250];
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
		escribir("curso.dot", dot, "a");
		
		graph(actual->siguiente);
	}
}

char* NodoCurso::toGraph()
{
	char nodo[8];
	sprintf(nodo, "CR%d", codigo);

	return nodo;
}

char* NodoCurso::toString()
{
	char nodo[80];
	sprintf(nodo, "%d\\n%d\\n", codigo, noCreditos);
	strcat(nodo, nombre);
	return nodo;
}