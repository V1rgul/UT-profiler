#include <QtDebug>
#include <QStandardItemModel>
#include "mainwindowcontroller.h"

#include "model/formationHorsUtc.h"
#include "formationcontroller.h"
#include "semestrecontroller.h"
#include "model/semestre.h"

MainWindowController::MainWindowController(QApplication& a):
	QObject(new MainWindow()), a(&a), mainWindow(qobject_cast<MainWindow*>(parent())), etudiant(0)
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

		update();
		foreach(FormationHorsUtc* f, etudiant->formationsHorsUtc()){
			addFormationToView(f);
		}
		foreach(Semestre* s, etudiant->formationUtc()->semestres()){
			addSemestreToView(s);
		}
	}

	qDebug() << "credits()" << etudiant->credits();
	qDebug() << "creditsNecessaires()" << etudiant->creditsNecessaires();
	//Init main Window Events
	connect(mainWindow, SIGNAL(nameChanged(QString,QString)), this, SLOT(nameChanged(QString,QString)));
	connect(mainWindow, SIGNAL(addFormationClicked()), this, SLOT(addFormation()));
	connect(mainWindow, SIGNAL(addSemestreClicked()), this, SLOT(addSemestre()));
	connect(a, SIGNAL(aboutToQuit()), this, SLOT(exiting()));

	mainWindow->show();
}


void MainWindowController::update(){
	QMap<QString, unsigned int> creditsObtenus = etudiant->credits();
	QMap<QString, unsigned int> creditsNecessaires = etudiant->creditsNecessaires();
	QStandardItemModel* model = new QStandardItemModel(2, creditsObtenus.count(), this);
	int column = 0;
	foreach (QString typeCredits, creditsNecessaires.keys()){
		QString creditsCount;
		creditsCount.append(QString::number(  creditsObtenus.contains(typeCredits) ? creditsObtenus.value(typeCredits) : 0  ));
		creditsCount.append(" / ");
		creditsCount.append(QString::number( creditsNecessaires.value(typeCredits) ));

		QStandardItem* typeItem = new QStandardItem(typeCredits);
		typeItem->setEditable(false);
		QStandardItem* creditsItem = new QStandardItem(creditsCount);
		creditsItem->setEditable(false);

		model->setItem(0, column, typeItem);
		model->setItem(1, column, creditsItem);
		column++;
	}
	QAbstractItemModel* old = mainWindow->swapModel(model);
	delete old;
	qDebug() << "Mainwindow update()";
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

void MainWindowController::addSemestre(){
	qDebug() << "add Semestre Clicked";

	Semestre* semestre = new Semestre();
	etudiant->formationUtc()->ajouterSemestre(semestre);

	addSemestreToView(semestre, true);
}
void MainWindowController::addFormation(){
	qDebug() << "add Formation Clicked";

	FormationHorsUtc* formation = new FormationHorsUtc();
	etudiant->ajouterFormation(formation);

	addFormationToView(formation);
}

void MainWindowController::addFormationToView(FormationHorsUtc* f){
	QFormation* qFormation = new QFormation();
	FormationController* formationController = new FormationController(f, qFormation);
	mainWindow->addFormation(qFormation);
	connect(formationController, SIGNAL(removed(FormationHorsUtc*)), this, SLOT(removeFormation(FormationHorsUtc*)));
	connect(formationController, SIGNAL(updated()), this, SLOT(update()));
}

void MainWindowController::addSemestreToView(Semestre* s, bool edit){
	QSemestre* qSemestre = new QSemestre();
	SemestreController* semestreController = new SemestreController(etudiant, s, qSemestre);
	mainWindow->addSemestre(qSemestre);
	connect(semestreController, SIGNAL(removed(Semestre*)), this, SLOT(removeSemestre(Semestre*)));
	connect(semestreController, SIGNAL(updated()), this, SLOT(update()));

	if(edit) semestreController->edit();
}

void MainWindowController::removeFormation(FormationHorsUtc *formation){
	qDebug() << "remove Formation Clicked";
	etudiant->supprimerFormation(formation->id());
	update();
}
void MainWindowController::removeSemestre(Semestre *semestre){
	qDebug() << "remove Semestre Clicked";
	etudiant->formationUtc()->supprimerSemestre(semestre->id());
	update();
}
