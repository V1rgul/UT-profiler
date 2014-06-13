#include "formationcontroller.h"


FormationController::FormationController(Formation* formation, QFormation* qFormation, QObject *parent) :
	QObject(parent), formation(formation), qFormation(qFormation), dialog(new QFormationDialog())
{
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));
	connect(dialog, SIGNAL(finished(int)), this, SLOT(dialogState(int)));
	loadInfo();
}

void FormationController::loadInfo(){
	qFormation->name(formation->nom());
}


void FormationController::edit(){
	//fill dialog
	dialog->name(formation->nom());

	dialog->show();


}

void FormationController::dialogState(int r){
	if( r == QDialog::Accepted ){
		//save data
		formation->nom(dialog->name());
		loadInfo();
	}
	dialog->close();
}

void FormationController::editEvent(){
	edit();
}

void FormationController::remove(){
	emit(removed(formation));
	emit(_removed());
}
