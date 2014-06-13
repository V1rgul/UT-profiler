#include "formationcontroller.h"


FormationController::FormationController(FormationHorsUtc* formation, QFormation* qFormation, QObject *parent) :
	QObject(parent), formation(formation), qFormation(qFormation)
{
	connect(this, SIGNAL(_removed()), qFormation, SLOT(deleteLater()));
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));

	qFormation->edit(formation->nom(), formation->credits());
}



void FormationController::editEvent(const QString name, const int credits){
	formation->nom(name);
	formation->credits(credits);
}

void FormationController::remove(){
	emit(removed(formation));
	emit(_removed());
}
