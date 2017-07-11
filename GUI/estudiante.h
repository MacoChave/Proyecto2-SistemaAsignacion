#include "lib.h"

class NodoEstudiante
{
public:
	NodoEstudiante();
	NodoEstudiante(int carnet, char *nombre_, char *direccion_);
	~NodoEstudiante();

	int carnet;
	char *nombre;
	char *direccion;
	int estado; //0 VACIO | 1 REMOVIDO | 2 OCUPADO

	char* toGraph();
	char* toString();
private:

};

class Estudiante
{
public:
	Estudiante();
	~Estudiante();

	int M;
	int m;
	double factorCarga;
	int T;
	NodoEstudiante *registros[37];

	void insertar(int carnet, char *nombre, char *direccion);
	void graph();
	double calcularFC();
	NodoEstudiante* buscar(int llv);
	bool eliminar(int llv);
	int h(int llv);
	int s(int llv, int i);
	void rehashing();
private:
	int siguientePrimo();
	void insertar(NodoEstudiante *r[], int carnet, char *nombre, char *direccion);
	void escribir(char filename[], char texto[], char *modo);
};
