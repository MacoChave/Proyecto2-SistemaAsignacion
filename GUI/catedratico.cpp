#include "lib.h"
#include "catedratico.h"

#pragma warning(disable:4996)

/**************************************************
 * CONSTRUCTORES Y DESTRUCTORES
**************************************************/
Catedratico::Catedratico()
{
	raiz = NULL;
}

Catedratico::~Catedratico()
{
	destructor(raiz);
	raiz = NULL;
}

void Catedratico::destructor(NodoCatedratico *actual)
{
	if (actual != NULL)
	{
		destructor(actual->derecha);
		destructor(actual->izquierda);
		delete(actual);
	}
	else
		return;
}

/**************************************************
* METODOS PUBLICOS
**************************************************/
void Catedratico::insertar(int id, char *nombre, char *direccion)
{
	if (raiz != NULL)
	{
		insertar(&raiz, id, nombre, direccion);
		getFE(raiz);
		equilibrar(&raiz);
	}
	else
		raiz = new NodoCatedratico(id, nombre, direccion);
}

void Catedratico::eliminar(int id)
{
	if (raiz != NULL)
	{
		eliminar(&raiz, id);
		getFE(raiz);
		equilibrar(&raiz);
	}
}

void Catedratico::graficar()
{
	char dot[256];
	strcpy_s(dot, "digraph arbolCatedratico\n{\n");
	strcat_s(dot, "\trankdir=TB;\n");
	strcat_s(dot, "\tnode [shape=record]\n");

	escribir("arbolCatedratico.dot", dot, 'w');
	strcpy_s(dot, "");

	graficar(raiz);

	escribir("arbolCatedratico.dot", "}", 'a');
	
	system("dot -Tpng arbolCatedratico.dot -o arbolCatedratico.png");
}

void Catedratico::modificar(int id, char *nombre, char *direccion)
{
	NodoCatedratico *actual = buscar(id);
	strcpy(actual->nombre, nombre);
	strcpy(actual->direccion, direccion);
}

/**************************************************
* METODOS PRIVADOS
**************************************************/
/*
 * ABC DEL ARBOL
 */
void Catedratico::insertar(NodoCatedratico **actual, int id, char *nombre, char *direccion)
{
	if ((*actual) != NULL)
	{
		if ((*actual)->id > id)
		{
			if ((*actual)->izquierda != NULL)
			{
				insertar(&((*actual)->izquierda), id, nombre, direccion);
				getFE((*actual));
				equilibrar(actual);
			}
			else
			{
				(*actual)->izquierda = new NodoCatedratico(id, nombre, direccion);
				getFE((*actual));
				equilibrar(actual);
			}
				
		}
		else if ((*actual)->id < id)
		{
			if ((*actual)->derecha != NULL)
			{
				insertar(&((*actual)->derecha), id, nombre, direccion);
				getFE((*actual));
				equilibrar(actual);
			}
			else
			{
				(*actual)->derecha = new NodoCatedratico(id, nombre, direccion);
				getFE((*actual));
				equilibrar(actual);
			}
		}
	}
}

void Catedratico::eliminar(NodoCatedratico **actual, int id)
{
	if ((*actual)->id > id)
	{
		if ((*actual)->izquierda != NULL)
			eliminar(&((*actual)->izquierda), id);
		else
			return;
	}
	else if ((*actual)->id < id)
	{
		if ((*actual)->derecha != NULL)
			eliminar(&((*actual)->derecha), id);
		else
			return;
	}
	else
	{
		if ((*actual)->izquierda == NULL && (*actual)->derecha == NULL)
			eliminarNodoHoja(actual);
		else
		{
			if ((*actual)->izquierda != NULL)
				eliminarNodoConHijoIzq(actual);
			else if ((*actual)->derecha != NULL)
				eliminarNodoConHijoDch(actual);
		}
	}

	if ((*actual) != NULL)
	{
		getFE((*actual));
		equilibrar(actual);
	}
}

/*
 * GRAFICAR ARBOL
 */
void Catedratico::graficar(NodoCatedratico *actual)
{
	if (actual != NULL)
	{
		char dot[128];
		char id[4];

		sprintf_s(id, " %d", actual->id);
		strcpy_s(dot, "\tnd");
		strcat_s(dot, actual->nombre);
		strcat_s(dot, "[label=\"<izq> | ");
		strcat_s(dot, actual->nombre);
		strcat_s(dot, id);
		strcat_s(dot, " | <dch>\"];\n");

		escribir("arbolCatedratico.dot", dot, 'a');

		if (actual->izquierda != NULL)
		{
			strcpy_s(dot, "\tnd");
			strcat_s(dot, actual->nombre);
			strcat_s(dot, " : izq -> nd");
			strcat_s(dot, actual->izquierda->nombre);
			strcat_s(dot, ";\n");

			escribir("arbolCatedratico.dot", dot, 'a');
		}

		if (actual->derecha != NULL)
		{
			strcpy_s(dot, "\tnd");
			strcat_s(dot, actual->nombre);
			strcat_s(dot, " : dch -> nd");
			strcat_s(dot, actual->derecha->nombre);
			strcat_s(dot, ";\n");

			escribir("arbolCatedratico.dot", dot, 'a');
		}

		graficar(actual->izquierda);
		graficar(actual->derecha);
	}
}

void Catedratico::escribir(char filename[], char texto[], char modo)
{
	char path[40];
	strcpy_s(path, filename);
	if (modo == 'w')
	{
		std::ofstream fs(path);
		fs << texto << std::endl;
		fs.close();
	}
	else
	{
		std::ofstream fs(path, std::ios::app);
		fs << texto << std::endl;
		fs.close();
	}
}

/*
 * EQUILIBRAR ARBOL
 */
void Catedratico::equilibrar(NodoCatedratico **actual)
{
	if ((*actual)->fe > 1)
	{
		if ((*actual)->derecha->fe == 1)
		{
			rotacion_SI(actual);
		}
		else
		{
			rotacion_DD(actual);
		}
	}
	else if ((*actual)->fe < -1)
	{
		if ((*actual)->izquierda->fe == 1)
		{
			rotacion_DI(actual);
		}
		else
		{
			rotacion_SD(actual);
		}
	}
}

void Catedratico::getFE(NodoCatedratico *actual)
{
	if (actual->izquierda != NULL)
		actual->hi = __max(actual->izquierda->hi, actual->izquierda->hd) + 1;
	else
		actual->hi = 0;
	if (actual->derecha != NULL)
		actual->hd = __max(actual->derecha->hi, actual->derecha->hd) + 1;
	else
		actual->hd = 0;

	actual->fe = actual->hd - actual->hi;
}

void Catedratico::rotacion_DD(NodoCatedratico **actual)
{
	rotacion_SD(&((*actual)->derecha));
	getFE((*actual));
	rotacion_SI(actual);
}

void Catedratico::rotacion_DI(NodoCatedratico **actual)
{
	rotacion_SI(&((*actual)->izquierda));
	getFE((*actual));
	rotacion_SD(actual);
}

void Catedratico::rotacion_SD(NodoCatedratico **actual)
{
	NodoCatedratico *temp = (*actual)->izquierda;
	(*actual)->izquierda = temp->derecha;
	temp->derecha = (*actual);

	getFE((*actual));
	getFE(temp);
	*actual = temp;
}

void Catedratico::rotacion_SI(NodoCatedratico **actual)
{
	NodoCatedratico *temp = (*actual)->derecha;
	(*actual)->derecha = temp->izquierda;
	temp->izquierda = (*actual);
	
	getFE((*actual));
	getFE(temp);
	*actual = temp;
}

void Catedratico::equilibrarMayores(NodoCatedratico **actual)
{
	if ((*actual)->derecha != NULL)
		return equilibrarMayores(&((*actual)->derecha));

	getFE((*actual));
	equilibrar(actual);
}

void Catedratico::equilibrarMenores(NodoCatedratico **actual)
{
	if ((*actual)->izquierda != NULL)
		return equilibrarMenores(&((*actual)->izquierda));

	getFE((*actual));
	equilibrar(actual);
}

/*
 * ELIMINACION DE NODOS
 */
void Catedratico::eliminarNodoHoja(NodoCatedratico **actual)
{
	NodoCatedratico *temp = *actual;
	delete(temp);
	(*actual) = NULL;
}

void Catedratico::eliminarNodoConHijoIzq(NodoCatedratico **actual)
{
	NodoCatedratico **mayor = mayores(&((*actual)->izquierda));
	
	(*actual)->id = (*mayor)->id;
	strcpy((*actual)->nombre, (*mayor)->nombre);
	strcpy((*actual)->direccion, (*mayor)->direccion);

	NodoCatedratico *temp = *mayor;
	*mayor = (*mayor)->izquierda;
	delete(temp);
	temp = NULL;

	if ((*actual)->izquierda != NULL)
		equilibrarMayores(&((*actual)->izquierda));
}

void Catedratico::eliminarNodoConHijoDch(NodoCatedratico **actual)
{
	NodoCatedratico **menor = menores(&((*actual)->derecha));
	
	(*actual)->id = (*menor)->id;
	strcpy((*actual)->nombre, (*menor)->nombre);
	strcpy((*actual)->direccion, (*menor)->direccion);

	NodoCatedratico *temp = *menor;
	(*menor) = (*menor)->derecha;
	delete(temp);
	temp = NULL;

	if ((*actual)->derecha != NULL)
		equilibrarMenores(&((*actual)->derecha));
}

NodoCatedratico** Catedratico::mayores(NodoCatedratico **actual)
{
	if ((*actual)->derecha != NULL)
		return mayores(&((*actual)->derecha));
	else
		return actual;
}

NodoCatedratico** Catedratico::menores(NodoCatedratico **actual)
{
	if ((*actual)->izquierda != NULL)
		return menores(&((*actual)->izquierda));
	else
		return actual;
}

/*
 * BUSCAR NODOS
 */
NodoCatedratico* Catedratico::buscar(NodoCatedratico *actual, int id)
{
	if (actual->id > id)
	{
		if (actual->izquierda != NULL)
			return buscar(actual->izquierda, id);
		else
			return NULL;
	}
	else if (actual->id < id)
	{
		if (actual->derecha != NULL)
			return buscar(actual->derecha, id);
		else
			return NULL;
	}
	else
		return actual;
}

NodoCatedratico* Catedratico::buscar(int id)
{
	if (raiz->id > id)
	{
		if (raiz->izquierda != NULL)
			return buscar(raiz->izquierda, id);
		else
			return NULL;
	}
	else if (raiz->id < id)
	{
		if (raiz->derecha != NULL)
			return buscar(raiz->derecha, id);
		else
			return NULL;
	}
	else
		return raiz;
}