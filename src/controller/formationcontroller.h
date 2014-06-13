#ifndef FORMATIONCONTROLLER_H
#define FORMATIONCONTROLLER_H

#include <QObject>
#include "qformation.h"
#include "model/formation.h"

class FormationController : public QObject
{
		Q_OBJECT
	public:
		explicit FormationController(Formation* formation, QFormation* qFormation, QObject *parent = 0);

	signals:

	public slots:
		void edit();
	private:
		Formation* formation;
		QFormation* qFormation;
};

#endif // FORMATIONCONTROLLER_H
