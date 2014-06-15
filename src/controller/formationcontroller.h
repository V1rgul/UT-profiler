#ifndef FORMATIONCONTROLLER_H
#define FORMATIONCONTROLLER_H

#include <QObject>
#include "qformation.h"
#include "model/formationHorsUtc.h"

class FormationController : public QObject
{
		Q_OBJECT
	public:
		explicit FormationController(FormationHorsUtc* formation, QFormation* qFormation, QObject *parent = 0);
	signals:
		void removed(FormationHorsUtc *formation);
		void _removed();
	public slots:
		void editEvent(QString name, int creditsCS, int creditsTM, int creditsTSH);
		void remove();

	private:
		FormationHorsUtc* formation;
		QFormation* qFormation;
};

#endif // FORMATIONCONTROLLER_H
