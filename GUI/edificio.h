#include "lib.h"
#include "salon.h"

class NodoEdificio
{
public:
	NodoEdificio(char *nombre_);
	~NodoEdificio();

	char *nombre;
	Salon *salones;
	NodoEdificio *anterior;
	NodoEdificio *siguiente;
	
	char* toGraph();
	char* toString();
private:

};

class Edificio
{
public:
	Edificio();
	~Edificio();

	NodoEdificio *primero;
	NodoEdificio *ultimo;

	void add(char *nombre);
	void addSalon(char *nombre, int numero, int capacidad);
	void remove(char *nombre);
	void removeSalon(char *nombre, int salon);
	NodoEdificio* getNodoEdificio(char *nombre);
	void graph();
private:
	void add(NodoEdificio *actual, char *nombre);
	void remove(NodoEdificio *actual, char *nombre);
	void removeSalon(NodoEdificio *actual, char *nombre, int salon);
	NodoEdificio* getNodoEdificio(NodoEdificio *actual, char *nombre);
	void escribir(char filename[], char texto[], char *modo);
	void graph(NodoEdificio *actual);
	void graphSalones(NodoEdificio *actual);
};
