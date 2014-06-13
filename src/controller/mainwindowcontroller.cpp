#include <QtDebug>
#include "mainwindowcontroller.h"

#include "model/formation.h"
#include "qformation.h"
#include "formationcontroller.h"

MainWindowController::MainWindowController(QApplication& a, QObject *parent):
	QObject(parent), a(&a), mainWindow(new MainWindow()), etudiant(0)
{
	userDialog = new QUserDialog();
	connect(userDialog, SIGNAL(selected(int)), this, SLOT(userSelect(int)));
	connect(userDialog, SIGNAL(rejected()), this, SLOT(userSelectRejected()));
	userDialog->show();



	/*
	QFormation formation1("Test Formation");
	w.addFormation(formation1);

	QSemestre semestre1;
	formation1.addSemestre(semestre1);
	*/
}


void MainWindowController::userSelect(const int index){
	qDebug() << "User selected:" << index;

	userDialog = 0;

	if( index == -1)
		etudiant = new Etudiant();
	else
		etudiant = /**/new Etudiant()/**/;

	//Init main Window
	connect(mainWindow, SIGNAL(nameChanged(QString,QString)), this, SLOT(nameChanged(QString,QString)));
	connect(mainWindow, SIGNAL(addFormationClicked()), this, SLOT(addFormation()));

	mainWindow->show();
}
void MainWindowController::userSelectRejected(){
	qDebug() << "User select rejected";
	a->exit();
}



void MainWindowController::nameChanged(const QString & name, const QString & surname){
	etudiant->nom(name);
	etudiant->prenom(surname);
}

void MainWindowController::addFormation(){
	qDebug() << "add Formation Clicked";
	QFormation* qFormation = new QFormation();
	FormationController* formationController = new FormationController(new Formation(), qFormation);
	formationController->edit();
	mainWindow->addFormation(qFormation);
}
