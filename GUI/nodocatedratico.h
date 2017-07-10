#pragma once
class NodoCatedratico
{
public:
	NodoCatedratico(int id, char *nombre_, char *direccion_);
	virtual ~NodoCatedratico();

	int id; /* ORDEN DEL Catedratico */
	char *nombre;
	char *direccion;
	int hi;
	int hd;
	int fe;
	NodoCatedratico *izquierda;
	NodoCatedratico *derecha;
};

