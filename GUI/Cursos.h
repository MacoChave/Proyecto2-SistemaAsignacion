#include "lib.h"

class NodoCurso
{
public:
	NodoCurso(int codigo_, char *nombre_, int semestre_, int noCreditos_);
	~NodoCurso();

	int codigo;
	char *nombre;
	int semestre;
	int noCreditos;
	NodoCurso *siguiente;

	char* toGraph();
	char* toString();
private:

};

class Curso
{
public:
	Curso();
	~Curso();

	NodoCurso *primero;
	NodoCurso *ultimo;

	void add(int codigo, char *nombre, int semestre, int noCreditos);
	void remove(int codigo);
	void editar(int coidgo_, char *nombre_, int semestre_, int noCreditos_);
	NodoCurso* buscar(int codigo_);
	void graph();
private:
	void add(NodoCurso *actual, int codigo, char *nombre, int semestre, int noCreditos);
	void remove(NodoCurso *actual, int codigo);
	void escribir(char filename[], char texto[], char *modo);
	void graph(NodoCurso *actual);
};
