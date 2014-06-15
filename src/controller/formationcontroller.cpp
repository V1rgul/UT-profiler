#include "formationcontroller.h"


FormationController::FormationController(FormationHorsUtc* formation, QFormation* qFormation, QObject *parent) :
	QObject(parent), formation(formation), qFormation(qFormation)
{
	connect(this, SIGNAL(_removed()), qFormation, SLOT(deleteLater()));
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));

	connect(qFormation, SIGNAL(edited(QString, int, int, int)), this, SLOT(editEvent(QString, int, int, int)));
	connect(qFormation, SIGNAL(remove()), this, SLOT(remove()));

	qFormation->edit(formation->nom(), formation->creditsCS(), formation->creditsTM(), formation->creditsTSH());
}



void FormationController::editEvent(QString name, int creditsCS, int creditsTM, int creditsTSH){
	formation->nom(name);
	formation->creditsCS(creditsCS);
	formation->creditsTM(creditsTM);
	formation->creditsTSH(creditsTSH);
	qDebug() << "formation credits changed";
}

void FormationController::remove(){
	emit(removed(formation));
	emit(_removed());
}
