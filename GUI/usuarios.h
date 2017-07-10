#include "lib.h"

class NodoUsuario
{
public:
	NodoUsuario(char *nombre_, char *pass_, char *tipo_);
	~NodoUsuario();

	char *nombre;
	char *pass;
	char *tipo;
	NodoUsuario *siguiente;
	NodoUsuario *anterior;

	char* toGraph();
	char* toString();
private:

};

class Usuario
{
public:
	Usuario();
	~Usuario();

	NodoUsuario *primero;
	NodoUsuario *ultimo;

	void add(char *nombre, char *pass, char *tipo);
	void remove(char *nombre);
	char* check(char *nombre, char *pass);
	void graph();
private:
	void add(NodoUsuario *actual, char *nombre, char *pass, char *tipo);
	void remove(NodoUsuario *actual, char *nombre);
	char* check(NodoUsuario *actual, char *nombre, char *pass);
	void graph(NodoUsuario *actual);
	void escribir(char filename[], char texto[], char *modo);
};
