#include "formationcontroller.h"
#include "qformationdialog.h"

FormationController::FormationController(Formation* formation, QFormation* qFormation, QObject *parent) :
	QObject(parent), formation(formation), qFormation(qFormation)
{
}


void FormationController::edit(){
	QFormationDialog dialog;

	//fill dialog

	if( dialog.exec() == QDialog::Accepted ){

		//save data
		//update data in qFormation
	}
}
