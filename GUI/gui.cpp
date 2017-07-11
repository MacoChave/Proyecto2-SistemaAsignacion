#include "gui.h"

GUI::GUI(const Wt::WEnvironment& env) : Wt::WApplication(env), ui(new Ui_GUI)
{
	ui->setupUi(root());
	listadoEdificio = new Edificio();
	listadoCurso = new Curso();
	listadoUsuario = new Usuario();
	arbolCatedratico = new Catedratico();
	hashEstudiante = new Estudiante();

	ocultarGrupos();

	ui->btnLogin->clicked().connect(this, &GUI::on_btnLoginClicked);
	ui->btnLogout->clicked().connect(this, &GUI::on_btnLogoutClicked);

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

	ui->btnFile->clicked().connect(this, &GUI::on_btnFileClicked);
	/* SUBIR CUANDO EL BOTON ES CLICKEADO 
	ui->btnFile->clicked().connect(ui->fileUp, &Wt::WFileUpload::upload);
	ui->btnFile->clicked().connect(ui->btnFile, &Wt::WPushButton::disable);
	*/
	/* SUBIR AUTOMATICAMENTE */
	ui->fileUp->changed().connect(ui->fileUp, &Wt::WFileUpload::upload);
}

GUI::~GUI()
{
	delete ui;
}

void GUI::ocultarGrupos()
{
	ui->grpLogin->show();
	ui->txtWarninLogin->hide();
	ui->grpEstudiante->hide();
	ui->grpUsuarios->hide();
	ui->grpEdificios->hide();
	ui->grpCursos->hide();
	ui->grpEstudiantes->hide();
	ui->grpCatedraticos->hide();
	ui->grpHorario->hide();
	ui->grpAsignaciones->hide();
	ui->grpReportes->hide();
	ui->grpArchivos->hide();
	ui->grpLogout->hide();
}

void GUI::on_btnLoginClicked()
{
	char *usuario = new char[strlen(ui->edtUserLogin->text().toUTF8().c_str())];
	char *pass = new char[strlen(ui->edtPassLogin->text().toUTF8().c_str())];
	strcpy(usuario, ui->edtUserLogin->text().toUTF8().c_str());
	strcpy(pass, ui->edtPassLogin->text().toUTF8().c_str());
	char tipo[15];
	strcpy(tipo, listadoUsuario->check(usuario, pass));
	
	if (strcmp(tipo, "colaborador") == 0)
	{
		ui->edtUserLogin->setText("");
		ui->edtPassLogin->setText("");

		ui->grpLogin->hide();
		ui->txtWarninLogin->hide();
		ui->grpEdificios->show();
		ui->grpCursos->show();
		ui->grpEstudiantes->show();
		ui->grpCatedraticos->show();
		ui->grpHorario->show();
		ui->grpAsignaciones->show();
		ui->grpReportes->show();
		ui->grpLogout->show();
	}
	else if (strcmp(tipo, "estudiante") == 0)
	{
		ui->edtUserLogin->setText("");
		ui->edtPassLogin->setText("");

		ui->grpLogin->hide();
		ui->txtWarninLogin->hide();
		ui->grpEstudiante->show();
		ui->grpLogout->show();
	}
	else if (strcmp(tipo, "super") == 0)
	{
		ui->edtUserLogin->setText("");
		ui->edtPassLogin->setText("");

		ui->grpLogin->hide();
		ui->txtWarninLogin->hide();
		ui->grpEdificios->show();
		ui->grpUsuarios->show();
		ui->grpCursos->show();
		ui->grpAsignaciones->show();
		ui->grpReportes->show();
		ui->grpArchivos->show();
		ui->grpLogout->show();
	}
	else
	{
		if (strcmp(usuario, "root") == 0 && strcmp(pass, "toor") == 0)
		{
			ui->edtUserLogin->setText("");
			ui->edtPassLogin->setText("");

			ui->grpLogin->hide();
			ui->txtWarninLogin->hide();
			ui->grpUsuarios->show();
			ui->grpArchivos->show();
			ui->grpLogout->show();
		}
		else
			ui->txtWarninLogin->show();
	}
}

void GUI::on_btnLogoutClicked()
{
	ocultarGrupos();
}

void GUI::on_btnAddClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str()) + 1];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{
		char *nombre = new char[strlen(ui->edtAddUsuario->text().toUTF8().c_str()) + 1];
		char *pass = new char[strlen(ui->edtAddPassUsuario->text().toUTF8().c_str()) + 1];
		char *tipo = new char[strlen(ui->edtAddTipoUsuario->text().toUTF8().c_str()) + 1];

		strcpy(nombre, ui->edtAddUsuario->text().toUTF8().c_str());
		strcpy(pass, ui->edtAddPassUsuario->text().toUTF8().c_str());
		strcpy(tipo, ui->edtAddTipoUsuario->text().toUTF8().c_str());

		listadoUsuario->add(nombre, pass, tipo);

		ui->edtAddUsuario->setText("");
		ui->edtAddPassUsuario->setText("");
		ui->edtAddTipoUsuario->setText("");

		ui->edtAddUsuario->setFocus(true);
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
		int carnet = atoi(ui->edtAddCarneEstudiante->text().toUTF8().c_str());
		char *nombre = new char[strlen(ui->edtAddNombreEstudiante->text().toUTF8().c_str()) + 1];
		strcpy(nombre, ui->edtAddNombreEstudiante->text().toUTF8().c_str());
		char *dir = new char[strlen(ui->edtAddCiudadEstudiante->text().toUTF8().c_str()) + 1];
		strcpy(dir, ui->edtAddCiudadEstudiante->text().toUTF8().c_str());

		hashEstudiante->insertar(carnet, nombre, dir);

		ui->edtAddCarneEstudiante->setText("");
		ui->edtAddNombreEstudiante->setText("");
		ui->edtAddCiudadEstudiante->setText("");
		ui->edtAddCarneEstudiante->setFocus(true);
	}
	if (strcmp(v, "Catedratico") == 0)
	{
		int id = atoi(ui->edtAddCodigoCatedratico->text().toUTF8().c_str());
		char *nombre = new char[strlen(ui->edtAddNombreCatedratico->text().toUTF8().c_str()) + 1];
		char *direccion = new char[strlen(ui->edtAddCiudadCatedratico->text().toUTF8().c_str()) + 1 ];

		strcpy(nombre, ui->edtAddNombreCatedratico->text().toUTF8().c_str());
		strcpy(direccion, ui->edtAddCiudadCatedratico->text().toUTF8().c_str());

		arbolCatedratico->insertar(id, nombre, direccion);

		ui->edtAddCodigoCatedratico->setText("");
		ui->edtAddNombreCatedratico->setText("");
		ui->edtAddCiudadCatedratico->setText("");

		ui->edtAddCodigoCatedratico->setFocus(true);
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
		int id = atoi(ui->edtEditCodigoCatedratico->text().toUTF8().c_str());
		char *nombre = new char[strlen(ui->edtEditNombreCatedratico->text().toUTF8().c_str()) + 1];
		char *direccion = new char[strlen(ui->edtEditCiudadCatedratico->text().toUTF8().c_str()) + 1];

		strcpy(nombre, ui->edtEditNombreCatedratico->text().toUTF8().c_str());
		strcpy(direccion, ui->edtEditCiudadCatedratico->text().toUTF8().c_str());

		arbolCatedratico->modificar(id, nombre, direccion);

		ui->edtEditCodigoCatedratico->setText("");
		ui->edtEditNombreCatedratico->setText("");
		ui->edtEditCiudadCatedratico->setText("");

		ui->edtEditCodigoCatedratico->setFocus(true);
	}
}

void GUI::on_btnDeleteClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str()) + 1];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{
		char *nombre = new char[strlen(ui->edtDeleteUsuario->text().toUTF8().c_str()) + 1];
		strcpy(nombre, ui->edtDeleteUsuario->text().toUTF8().c_str());

		listadoUsuario->remove(nombre);

		ui->edtDeleteUsuario->setText("");
		ui->edtDeleteUsuario->setFocus(true);
	}
	if (strcmp(v, "Edificio") == 0)
	{
		char *nombre = new char[strlen(ui->edtDeleteNombreEdificio->text().toUTF8().c_str()) + 1];
		strcpy(nombre, ui->edtDeleteNombreEdificio->text().toUTF8().c_str());

		listadoEdificio->remove(nombre);

		ui->edtDeleteNombreEdificio->setText("");
		ui->edtDeleteNombreEdificio->setFocus(true);
	}
	if (strcmp(v, "Salon") == 0)
	{
		char *edificio = new char[strlen(ui->edtDeleteEdificioSalon->text().toUTF8().c_str()) + 1];
		int salon = atoi(ui->edtDeleteCodigoSalon->text().toUTF8().c_str());

		strcpy(edificio, ui->edtDeleteEdificioSalon->text().toUTF8().c_str());

		listadoEdificio->removeSalon(edificio, salon);

		ui->edtDeleteEdificioSalon->setText("");
		ui->edtDeleteCodigoSalon->setText("");
		ui->edtDeleteEdificioSalon->setFocus(true);
	}
	if (strcmp(v, "Curso") == 0)
	{
		int codigo = atoi(ui->edtDeleteCodigoCurso->text().toUTF8().c_str());

		listadoCurso->remove(codigo);

		ui->edtDeleteCodigoCurso->setText("");
		ui->edtDeleteCodigoCurso->setFocus(true);
	}
	if (strcmp(v, "Estudiante") == 0)
	{

	}
	if (strcmp(v, "Catedratico") == 0)
	{
		int id = atoi(ui->edtDeleteCodigoCatedratico->text().toUTF8().c_str());

		arbolCatedratico->eliminar(id);

		ui->edtDeleteCodigoCatedratico->setText("");
		ui->edtDeleteCodigoCatedratico->setFocus(true);
	}
}

void GUI::on_btnGraficoClicked(Wt::WString value)
{
	char *v;
	v = new char[strlen(value.toUTF8().c_str() + 1)];
	strcpy(v, value.toUTF8().c_str());

	if (strcmp(v, "Usuario") == 0)
	{
		listadoUsuario->graph();
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
		hashEstudiante->graph();
	}
	if (strcmp(v, "Catedraticos") == 0)
	{
		arbolCatedratico->graficar();
	}
	if (strcmp(v, "Horarios") == 0)
	{

	}
	if (strcmp(v, "Asignaciones") == 0)
	{

	}
}

void GUI::on_btnFileClicked()
{
	//char *path = new char[strlen(ui->fileupload->text().toUTF8().c_str()) + 1];
	//strcpy(path, ui->fileupload->text().toUTF8().c_str());
	char *filename;
	if (ui->fileUp->canUpload())
	{
		ui->fileUp->upload();
		ui->fileUp->uploaded();
		filename = new char[strlen(ui->fileUp->spoolFileName().c_str()) + 1];
		strcpy(filename, ui->fileUp->spoolFileName().c_str());
	}

	//cargarArchivo("C:/Users/Totto/Desktop/datos.txt");
	cargarArchivo(filename);
}

void GUI::cargarArchivo(char *path)
{
	char linea[128];
	char campo1[25];
	char campo2[25];
	char campo3[30];
	char campo4[25];
	char campo5[25];

	FILE *archivo;
	archivo = fopen(path, "r");

	if (archivo != NULL)
	{
		while (!feof(archivo))
		{
			fgets(linea, 128, archivo);

			strcpy(campo1, strtok(linea, "()\",; "));
			if (strcmp(campo1, "Usuario") == 0)
			{
				strcpy(campo2, strtok(NULL, "()\",; "));
				strcpy(campo3, strtok(NULL, "()\",; "));
				strcpy(campo4, strtok(NULL, "()\",; "));

				listadoUsuario->add(campo2, campo3, campo4);
			}
			if (strcmp(campo1, "Estudiante") == 0)
			{
				strcpy(campo2, strtok(NULL, "()\",; "));
				strcpy(campo3, strtok(NULL, "()\",; "));
				strcpy(campo4, strtok(NULL, "()\",; "));

				hashEstudiante->insertar(atoi(campo2), campo3, campo4);
			}
			if (strcmp(campo1, "Catedratico") == 0)
			{
				strcpy(campo2, strtok(NULL, "()\",; "));
				strcpy(campo3, strtok(NULL, "()\",; "));
				strcpy(campo4, strtok(NULL, "()\",; "));

				arbolCatedratico->insertar(atoi(campo2), campo3, campo4);
			}
			if (strcmp(campo1, "Edificio") == 0)
			{
				strcpy(campo2, strtok(NULL, "()\",; "));

				listadoEdificio->add(campo2);
			}
			if (strcmp(campo1, "Salon") == 0)
			{
				strcpy(campo2, strtok(NULL, "()\",; "));
				strcpy(campo3, strtok(NULL, "()\",; "));
				strcpy(campo4, strtok(NULL, "()\",; "));

				listadoEdificio->addSalon(campo2, atoi(campo3), atoi(campo4));
			}
			if (strcmp(campo1, "Curso") == 0)
			{
				strcpy(campo2, strtok(NULL, "()\",; "));
				strcpy(campo3, strtok(NULL, "()\",; "));
				strcpy(campo4, strtok(NULL, "()\",; "));
				strcpy(campo5, strtok(NULL, "()\",; "));

				listadoCurso->add(atoi(campo2), campo3, atoi(campo4), atoi(campo5));
			}
		}

		fclose(archivo);
	}
}