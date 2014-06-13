#include "etudiantcontroller.h"

EtudiantController::EtudiantController(QWidget* tabEtudiant, Etudiant etudiant, QObject *parent = 0) :
	QObject(parent), tabEtudiant(tabEtudiant), etudiant(etudiant)
{
	connect(tabEtudiant->ui);
}

EtudiantController::EtudiantController(QWidget* tabEtudiant, Etudiant etudiant, QObject *parent = 0) :
	EtudiantController(tabEtudiant, new Etudiant())
{
}



void EtudiantController::nameChanged(QString name, QString surname){
	etudiant->nom(name);
	etudiant->prenom(surname);
}
