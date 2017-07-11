#include "lib.h"

class NodoSalon
{
public:
	NodoSalon(int numero_, int capacidad_);
	~NodoSalon();

	int numero;
	int capacidad;
	NodoSalon *siguiente;
	char *toGraph();
	char *toString();
private:

};

class Salon
{
public:
	Salon();
	~Salon();
	
	NodoSalon *primero;
	NodoSalon *ultimo;

	void add(int numero, int capacidad);
	void remove(int numero);
	void clear();
	void graph();
	void escribir(char filename[], char texto[], char *modo);
private:
	void add(NodoSalon *actual, int numero, int capacidad);
	void remove(NodoSalon *actual, int numero);
	void clear(NodoSalon **actual);
	void graph(NodoSalon *actual);
};
