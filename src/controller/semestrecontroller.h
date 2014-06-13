#ifndef SEMESTRECONTROLLER_H
#define SEMESTRECONTROLLER_H

#include <QObject>
#include "model/semestre.h"
#include "qsemestre.h"

class SemestreController : public QObject
{
		Q_OBJECT
	public:
		explicit SemestreController(Semestre* semestre, QSemestre* qSemestre, QObject *parent = 0);
		void loadInfo();
	signals:

	public slots:

	private:
		Semestre* semestre;
		QSemestre* qSemestre;
};

#endif // SEMESTRECONTROLLER_H
