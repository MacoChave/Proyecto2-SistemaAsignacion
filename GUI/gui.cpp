#include "gui.h"

GUI::GUI(const Wt::WEnvironment& env) : Wt::WApplication(env), ui(new Ui_GUI)
{
	ui->setupUi(root());
	listadoEdificio = new Edificio();
	listadoCurso = new Curso();
	ocultarGrupos();

	ui->btnLogin->clicked().connect(this, &GUI::on_btnLoginClicked);

	ui->btnAddUsuario->clicked().connect(boost::bind(&GUI::on_btnAddClicked, this, "Usuario"));
	ui->btnAddEdificio->clicked().connect(boost::bind(&GUI::on_btnAddClicked, this, "Edificio"));
	ui->btnAddSalon->clicked().connect(boost::bind(&GUI::on_btnAddClicked, this, "Salon"));
	ui->btnAddCurso->clicked().connect(boost::bind(&GUI::on_btnAddClicked, this, "Curso"));
	ui->btnAddEstudiante->clicked().connect(boost::bind(&GUI::on_btnAddClicked, this, "Estudiante"));
	ui->btnAddCatedratico->clicked().connect(boost::bind(&GUI::on_btnAddClicked, this, "Catedratico"));

	ui->btnEditUsuario->clicked().connect(boost::bind(&GUI::on_btnEditClicked, this, "Usuario"));
	ui->btnEditEdificio->clicked().connect(boost::bind(&GUI::on_btnEditClicked, this, "Edificio"));
	ui->btnEditSalon->clicked().connect(boost::bind(&GUI::on_btnEditClicked, this, "Salon"));
	ui->btnEditCurso->clicked().connect(boost::bind(&GUI::on_btnEditClicked, this, "Curso"));
	ui->btnEditEstudiante->clicked().connect(boost::bind(&GUI::on_btnEditClicked, this, "Estudiante"));
	ui->btnEditCatedratico->clicked().connect(boost::bind(&GUI::on_btnEditClicked, this, "Catedratico"));

	ui->btnDeleteUsuario->clicked().connect(boost::bind(&GUI::on_btnDeleteClicked, this, "Usuario"));
	ui->btnDeleteEdificio->clicked().connect(boost::bind(&GUI::on_btnDeleteClicked, this, "Edificio"));
	ui->btnDeleteSalon->clicked().connect(boost::bind(&GUI::on_btnDeleteClicked, this, "Salon"));
	ui->btnDeleteCurso->clicked().connect(boost::bind(&GUI::on_btnDeleteClicked, this, "Curso"));
	ui->btnDeleteEstudiante->clicked().connect(boost::bind(&GUI::on_btnDeleteClicked, this, "Estudiante"));
	ui->btnDeleteCatedratico->clicked().connect(boost::bind(&GUI::on_btnDeleteClicked, this, "Catedratico"));
	
	ui->btnGraficoUsuario->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "Usuario"));
	ui->btnGraficoEyS->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "EyS"));
	ui->btnGraficoCursos->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "Cursos"));
	ui->btnGraficoEstudiantes->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "Estudiantes"));
	ui->btnGraficoCatedraticos->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "Catedraticos"));
	ui->btnGraficoHorarios->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "Horarios"));
	ui->btnGraficoAsignaciones->clicked().connect(boost::bind(&GUI::on_btnGraficoClicked, this, "Asignaciones"));
}

GUI::~GUI()
{
	delete ui;
}

void GUI::ocultarGrupos()
{
	ui->grpLogin->setStyleClass("group");
	ui->grpEstudiante->setStyleClass("ocultar");
	ui->grpUsuarios->setStyleClass("ocultar");
	ui->grpEdificios->setStyleClass("ocultar");
	ui->grpCursos->setStyleClass("ocultar");
	ui->grpEstudiantes->setStyleClass("ocultar");
	ui->grpCatedraticos->setStyleClass("ocultar");
	ui->grpHorario->setStyleClass("ocultar");
	ui->grpAsignaciones->setStyleClass("ocultar");
	ui->grpReportes->setStyleClass("ocultar");
	ui->grpArchivos->setStyleClass("ocultar");
}

void GUI::on_btnLoginClicked()
{

}

void GUI::on_btnAddClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str()) + 1];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{

	}
	if (strcmp(v, "Edificio") == 0)
	{
		char *nombre = new char[strlen(ui->edtAddNombreEdificio->text().toUTF8().c_str()) + 1];
		strcpy(nombre, ui->edtAddNombreEdificio->text().toUTF8().c_str());

		listadoEdificio->add(nombre);

		ui->edtAddNombreEdificio->setText("");
		ui->edtAddNombreEdificio->setFocus(true);
	}
	if (strcmp(v, "Salon") == 0)
	{
		char *nombre = new char[strlen(ui->edtAddEdificioSalon->text().toUTF8().c_str()) + 1];
		int numero;
		int capacidad;
		strcpy(nombre, ui->edtAddEdificioSalon->text().toUTF8().c_str());
		numero = atoi(ui->edtAddNumeroSalon->text().toUTF8().c_str());
		capacidad = atoi(ui->edtAddCapacidadSalon->text().toUTF8().c_str());

		listadoEdificio->addSalon(nombre, numero, capacidad);

		ui->edtAddEdificioSalon->setText("");
		ui->edtAddNumeroSalon->setText("");
		ui->edtAddCapacidadSalon->setText("");

		ui->edtAddEdificioSalon->setFocus(true);
	}
	if (strcmp(v, "Curso") == 0)
	{
		int codigo;
		char *nombre = new char[strlen(ui->edtAddNombreCurso->text().toUTF8().c_str()) + 1];
		int semestre;
		int noCreditos;
		codigo = atoi(ui->edtAddCodigoCurso->text().toUTF8().c_str());
		strcpy(nombre, ui->edtAddNombreCurso->text().toUTF8().c_str());
		semestre = atoi(ui->edtAddSemestreCurso->text().toUTF8().c_str());
		noCreditos = atoi(ui->edtAddCreditoCurso->text().toUTF8().c_str());

		listadoCurso->add(codigo, nombre, semestre, noCreditos);

		ui->edtAddCodigoCurso->setText("");
		ui->edtAddNombreCurso->setText("");
		ui->edtAddSemestreCurso->setText("");
		ui->edtAddCreditoCurso->setText("");

		ui->edtAddCodigoCurso->setFocus(true);
	}
	if (strcmp(v, "Estudiante") == 0)
	{

	}
	if (strcmp(v, "Catedratico") == 0)
	{

	}
}

void GUI::on_btnEditClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str()) + 1];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{

	}
	if (strcmp(v, "Edificio") == 0)
	{

	}
	if (strcmp(v, "Salon") == 0)
	{

	}
	if (strcmp(v, "Curso") == 0)
	{

	}
	if (strcmp(v, "Estudiante") == 0)
	{

	}
	if (strcmp(v, "Catedratico") == 0)
	{

	}
}

void GUI::on_btnDeleteClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str()) + 1];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{

	}
	if (strcmp(v, "Edificio") == 0)
	{

	}
	if (strcmp(v, "Salon") == 0)
	{

	}
	if (strcmp(v, "Curso") == 0)
	{

	}
	if (strcmp(v, "Estudiante") == 0)
	{

	}
	if (strcmp(v, "Catedratico") == 0)
	{

	}
}

void GUI::on_btnGraficoClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str() + 1)];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{

	}
	if (strcmp(v, "EyS") == 0)
	{
		listadoEdificio->graph();
	}
	if (strcmp(v, "Cursos") == 0)
	{
		listadoCurso->graph();
	}
	if (strcmp(v, "Estudiantes") == 0)
	{

	}
	if (strcmp(v, "Catedraticos") == 0)
	{

	}
	if (strcmp(v, "Horarios") == 0)
	{

	}
	if (strcmp(v, "Asignaciones") == 0)
	{

	}
}