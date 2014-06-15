#include "formationcontroller.h"


FormationController::FormationController(FormationHorsUtc* formation, QFormation* qFormation, QObject *parent) :
	QObject(parent), formation(formation), qFormation(qFormation)
{
	connect(this, SIGNAL(_removed()), qFormation, SLOT(deleteLater()));
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));

	connect(qFormation, SIGNAL(edited(QString,int)), this, SLOT(editEvent(QString,int)));
	connect(qFormation, SIGNAL(remove()), this, SLOT(remove()));

	qFormation->edit(formation->nom(), /*formation->credits()*/42);
}



void FormationController::editEvent(const QString name, const int credits){
	formation->nom(name);
	//formation->credits(credits);
	qDebug() << "Formation setted to " << credits << " credits";
}

void FormationController::remove(){
	emit(removed(formation));
	emit(_removed());
}


/*/////////////////// Change Credits //////////////////*/
