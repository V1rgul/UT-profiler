#ifndef FORMATIONCONTROLLER_H
#define FORMATIONCONTROLLER_H

#include <QObject>
#include "qformation.h"
#include "model/formation.h"
#include "qformationdialog.h"

class FormationController : public QObject
{
		Q_OBJECT
	public:
		explicit FormationController(Formation* formation, QFormation* qFormation, QObject *parent = 0);
		void edit();
	signals:
		void removed(Formation *formation);
		void _removed();
	public slots:
		void editEvent();
		void remove();

		void dialogState(int r);
	private:
		void loadInfo();
		Formation* formation;
		QFormation* qFormation;

		QFormationDialog* dialog;
};

#endif // FORMATIONCONTROLLER_H
