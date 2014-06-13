#include "formationcontroller.h"
#include "qformationdialog.h"

FormationController::FormationController(Formation* formation, QFormation* qFormation, QObject *parent) :
	QObject(parent), formation(formation), qFormation(qFormation)
{
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));
}


int FormationController::edit(){
	QFormationDialog dialog;

	//fill dialog
	//connects

	if( dialog.exec() == QDialog::Accepted ){

		//save data
		//update data in qFormation
		return QDialog::Accepted;
	}
	return QDialog::Rejected;
}

void FormationController::editEvent(){
	edit();
}

void FormationController::remove(){
	emit(removed(formation));
	emit(_removed());
}

