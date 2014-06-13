#include <QtDebug>
#include "mainwindowcontroller.h"

#include "model/formationHorsUtc.h"
#include "formationcontroller.h"

MainWindowController::MainWindowController(QApplication& a, QObject *parent):
	QObject(parent), a(&a), mainWindow(new MainWindow()), etudiant(0)
{
	etudiantList = Etudiant::listeEtudiants();
	qDebug() << "etudiant list" << etudiantList;
	userDialog = new QUserDialog(etudiantList);
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

	//Init main Window Data
	if( index == -1)
		etudiant = new Etudiant();
	else{
		etudiant = Etudiant::charger(etudiantList.at(index));
		mainWindow->setName(etudiant->nom(), etudiant->prenom());
		foreach(FormationHorsUtc* f, etudiant->formationsHorsUtc()){
			QFormation* qFormation = new QFormation();
			FormationController* formationController = new FormationController(f, qFormation);
			mainWindow->addFormation(qFormation);
			connect(formationController, SIGNAL(removed(FormationHorsUtc*)), this, SLOT(removeFormation(FormationHorsUtc*)));
		}
	}

	//Init main Window Events
	connect(mainWindow, SIGNAL(nameChanged(QString,QString)), this, SLOT(nameChanged(QString,QString)));
	connect(mainWindow, SIGNAL(addFormationClicked()), this, SLOT(addFormation()));
	connect(a, SIGNAL(aboutToQuit()), this, SLOT(exiting()));

	mainWindow->show();
}
void MainWindowController::userSelectRejected(){
	qDebug() << "User select rejected";
	a->exit();
}

void MainWindowController::exiting(){
	qDebug() << "exiting procedure started, saving...";
	etudiant->sauvegarder();
}



void MainWindowController::nameChanged(const QString & name, const QString & surname){
	etudiant->nom(name);
	etudiant->prenom(surname);
}

void MainWindowController::addFormation(){
	qDebug() << "add Formation Clicked";
	QFormation* qFormation = new QFormation();
	FormationHorsUtc* formation = new FormationHorsUtc();
	FormationController* formationController = new FormationController(formation, qFormation);
	mainWindow->addFormation(qFormation);
	etudiant->ajouterFormation(formation);
	connect(formationController, SIGNAL(removed(FormationHorsUtc*)), this, SLOT(removeFormation(FormationHorsUtc*)));
}

void MainWindowController::removeFormation(FormationHorsUtc *formation){
	qDebug() << "remove Formation Clicked";
	etudiant->supprimerFormation(formation->id());
}
