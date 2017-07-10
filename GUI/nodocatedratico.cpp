#include "lib.h"
#include "nodocatedratico.h"


NodoCatedratico::NodoCatedratico(int id_, char *nombre_, char *direccion_)
{
	id = id_;
	nombre = new char[strlen(nombre_) + 1];
	strcpy_s(nombre, strlen(nombre_) + 1, nombre_);
	direccion = new char[strlen(direccion_) + 1];
	strcpy_s(direccion, strlen(direccion_) + 1, direccion_);
	hi = 0;
	hd = 0;
	fe = 0;
	izquierda = NULL;
	derecha = NULL;
}

NodoCatedratico::~NodoCatedratico()
{
	delete[](nombre);
	delete[](direccion);
	izquierda = NULL;
	derecha = NULL;
}
