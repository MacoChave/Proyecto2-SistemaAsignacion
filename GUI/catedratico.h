#pragma once
#include "nodocatedratico.h"
#include <fstream>

class Catedratico
{
	void destructor(NodoCatedratico *actual);
	
	/* ABC DEL ARBOL */
	void insertar(NodoCatedratico **actual, int id, char *nombre, char *direccion);
	void eliminar(NodoCatedratico **actual, int id);
	
	/* GRAFICAR ARBOL */
	void graficar(NodoCatedratico *actual);
	void escribir(char filename[], char texto[], char modo);
	
	/* EQUILIBRAR ARBOL */
	void equilibrar(NodoCatedratico **actual);
	void getFE(NodoCatedratico *actual);
	void rotacion_DI(NodoCatedratico **actual);
	void rotacion_DD(NodoCatedratico **actual);
	void rotacion_SI(NodoCatedratico **actual);
	void rotacion_SD(NodoCatedratico **actual);
	void equilibrarMayores(NodoCatedratico **actual);
	void equilibrarMenores(NodoCatedratico **actual);

	/* ELIMINACION DE NODOS */
	void eliminarNodoHoja(NodoCatedratico **actual);
	void eliminarNodoConHijoIzq(NodoCatedratico **actual);
	void eliminarNodoConHijoDch(NodoCatedratico **actual);
	NodoCatedratico** mayores(NodoCatedratico **actual);
	NodoCatedratico** menores(NodoCatedratico **actual);

	/* BUSCAR NODOS */
	NodoCatedratico* buscar(NodoCatedratico *actual, int id);
public:
	Catedratico();
	virtual ~Catedratico();

	NodoCatedratico *raiz;

	void insertar(int id, char *nombre, char *direccion);
	void eliminar(int id);
	void graficar();
	void modificar(int id, char *nombre, char *direccion);
	NodoCatedratico* buscar(int id);
};

