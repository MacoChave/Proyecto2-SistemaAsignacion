#include "estudiante.h"

NodoEstudiante::NodoEstudiante()
{
	carnet = 0;
	estado = 0;
}

NodoEstudiante::NodoEstudiante(int carnet, char *nombre_, char *direccion_)
{
	carnet = carnet;
	nombre = new char[strlen(nombre_) + 1];
	strcpy(nombre, nombre_);
	direccion = new char[strlen(direccion_) + 1];
	strcpy(direccion, direccion_);
	estado = 1;
}

NodoEstudiante::~NodoEstudiante()
{
	carnet = 0;
	delete[](nombre);
	delete[](direccion);
	estado = 2;
}

Estudiante::Estudiante()
{
	M = 37;
	m = 37;
	T = 0;
	factorCarga = 0;
	this->registros = new NodoEstudiante*[M];

	for (int i = 0; i < M; i++)
		registros[i] = new NodoEstudiante();
}

Estudiante::~Estudiante()
{
}

int Estudiante::h(int llv)
{
	return llv % M;
}

int Estudiante::s(int llv, int i)
{
	return (llv % 7 + 1) * i;
}

void Estudiante::insertar(int carnet, char *nombre, char *direccion)
{
	insertar(registros, carnet, nombre, direccion);
}

void Estudiante::insertar(NodoEstudiante **r, int carnet, char *nombre, char *direccion)
{
	int f = h(carnet);

	if (r[f]->estado == 0)
	{
		/* CELDA LIBRE */
		r[f]->carnet = carnet;
		r[f]->nombre = new char[strlen(nombre) + 1];
		strcpy(r[f]->nombre, nombre);
		r[f]->direccion = new char[strlen(direccion) + 1];
		strcpy(r[f]->direccion, direccion);
		r[f]->estado = 1;
		T++;
	}
	else
	{
		/* CELDA OCUPADA O ELIMINADA*/
		int i = 1;
		while (true)
		{
			int c = f + s(carnet, i);
			while (c >= M)
				c = c - M;

			if (r[c]->estado != 1)
			{
				/* CELDA LIBRE */
				r[c]->carnet = carnet;
				r[c]->nombre = new char[strlen(nombre) + 1];
				strcpy(r[c]->nombre, nombre);
				r[c]->direccion = new char[strlen(direccion) + 1];
				strcpy(r[c]->direccion, direccion);
				r[c]->estado = 1;
				T++;
				break;
			}
			i++;
		}
	}

	factorCarga = calcularFC();

	if (factorCarga >= 55)
		rehashing();
}

void Estudiante::editar(int carnet, char *nombre, char *direccion)
{
	int f = h(carnet);

	if (registros[f]->estado == 1)
	{
		/* CELDA CON ALGUN DATO */
		if (registros[f]->carnet == carnet)
		{
			/* COPIAR VALORES */
			registros[f]->carnet = carnet;
			strcpy(registros[f]->nombre, nombre);
			strcpy(registros[f]->direccion, direccion);
			registros[f]->estado = 1;
		}
		else
		{
			/* CELDA CON OTRO DATO */
			int i = 1;
			while (true)
			{
				int c = f + s(carnet, i);
				while (c > M)
					c = c - M;

				if (registros[c]->estado != 1)
				{
					/* COPIAR VALORES */
					registros[c]->carnet = carnet;
					strcpy(registros[c]->nombre, nombre);
					strcpy(registros[c]->direccion, direccion);
					registros[c]->estado = 1;
					break;
				}
				i++;
			}
		}
	}

	factorCarga = calcularFC();
}

bool Estudiante::eliminar(int llv)
{
	int f = h(llv);

	if (registros[f]->estado == 1)
	{
		/* CELDA CON ALGUN DATO */
		if (registros[f]->carnet == llv)
		{
			delete(registros[f]);
			T--;
		}
		else
		{
			/* CELDA CON OTRO DATO */
			int i = 1;
			while (true)
			{
				int c = f + s(llv, i);
				while (c > M)
					c = c - M;

				if (registros[c]->estado != 1)
				{
					delete(registros[c]);
					T--;
					break;
				}
				i++;
			}
		}
	}

	factorCarga = calcularFC();

	return true;
}

double Estudiante::calcularFC()
{
	return (T * 100) / M;
}

void Estudiante::rehashing()
{
	m = M;
	int m_ = 0;
	m_ = siguientePrimo();
	M = m_;
	T = 0;
	NodoEstudiante **nuevoRegistro;
	nuevoRegistro = new NodoEstudiante*[M];
	for (int i = 0; i < M; i++)
		nuevoRegistro[i] = new NodoEstudiante();

	for (int i = 0; i < m; i++)
	{
		if (registros[i]->estado == 1)
		{
			insertar(nuevoRegistro, registros[i]->carnet, registros[i]->nombre, registros[i]->direccion);
		}
	}

	NodoEstudiante **temp = registros;

	registros = nuevoRegistro;

	for (int i = 0; i < m; i++)
	{
		if (temp[i]->estado == 1)
		{
			temp[i]->carnet = 0;
			delete[](temp[i]->nombre);
			delete[](temp[i]->direccion);
			temp[i]->estado = 2;
			//delete(temp[i]);
		}
	}

	delete[](temp);
}

void Estudiante::escribir(char filename[], char texto[], char *modo)
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

void Estudiante::graph()
{
	char dot[150];
	strcpy(dot, "digraph estudiante {\n");
	strcat(dot, "\tnodesep=.05;\n");
	strcat(dot, "rankdir=RL");
	strcat(dot, "\tnode [shape=record,width=1.5,height=.5];\n");

	strcat(dot, "HASH[label=\"");

	escribir("estudiante.dot", dot, "w");

	for (int i = 0; i < M; i++)
	{
		if (registros[i]->estado == 1)
			strcpy(dot, registros[i]->nombre);
		else
			strcpy(dot, " ");
		strcat(dot, " | ");

		escribir("estudiante.dot", dot, "a");
	}

	strcpy(dot, "\"];\n}");

	escribir("estudiante.dot", dot, "a");

	system("dot -Tpng estudiante.dot -o estudiante.png");
}

int Estudiante::siguientePrimo()
{
	int x = M + 1;

	while (true)
	{
		int d = 0;
		for (int i = 2; i <= x / 2; i++)
		{
			if (x % i == 0)
				d++;
		}
		if (d < 2)
			break;
		else
			x++;
	}

	return x;
}