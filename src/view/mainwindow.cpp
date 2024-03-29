#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->buttonAddFormation, SIGNAL(clicked()), this, SLOT(buttonAddFormationClicked()));
	connect(ui->buttonAddSemestre, SIGNAL(clicked()), this, SLOT(buttonAddSemestreClicked()));
	connect(ui->editNom, SIGNAL(textChanged(QString)), this, SLOT(editNameChanged(QString)));
	connect(ui->editPrenom, SIGNAL(textChanged(QString)), this, SLOT(editSurnameChanged(QString)));
}

MainWindow::~MainWindow()
{
	qDebug() << "calling destructor of MainWindow";
	delete ui;
}

void MainWindow::setName(const QString &name, const QString &surname){
	ui->editNom->setText(name);
	ui->editPrenom->setText(surname);
}

void MainWindow::addFormation(QFormation* formation){
	ui->layoutFormations->addWidget(formation);
}
void MainWindow::addSemestre(QSemestre *semestre){
	ui->layoutSemestres->addWidget(semestre);
}

void MainWindow::buttonAddFormationClicked(){
	qDebug() << "addFormation clicked";
	emit(addFormationClicked());
}
void MainWindow::buttonAddSemestreClicked(){
	qDebug() << "addSemestre clicked";
	emit(addSemestreClicked());
}

void MainWindow::editNameChanged(const QString & text){
	qDebug() << "nameChanged" << text << ui->editPrenom->text();
	emit(nameChanged(text, ui->editPrenom->text()));
}
void MainWindow::editSurnameChanged(const QString & text){
	qDebug() << "nameChanged" << ui->editNom->text() <<  text;
	emit(nameChanged(ui->editNom->text(), text));
}
QAbstractItemModel* MainWindow::swapModel(QAbstractItemModel* model){
	QAbstractItemModel* old = ui->tableView->model();
	ui->tableView->setModel(model);
	return old;
}


