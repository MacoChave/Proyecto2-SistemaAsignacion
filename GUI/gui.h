#ifndef GUI_H
#define GUI_H

#include <Wt/WApplication>

#include "ui_gui.h"
#include "edificio.h"
#include "Cursos.h"

class GUI : public Wt::WApplication
{

public:
	GUI(const Wt::WEnvironment& env);
	~GUI();

	void ocultarGrupos();
	// declare slots here
	void on_btnLoginClicked();
	
	void on_btnAddClicked(Wt::WString value);
	void on_btnEditClicked(Wt::WString value);
	void on_btnDeleteClicked(Wt::WString value);

	void on_btnGraficoClicked(Wt::WString value);
private:
	Ui_GUI *ui;
	Edificio *listadoEdificio;
	Curso *listadoCurso;
};

#endif // GUI_H