#ifndef SEMESTRECONTROLLER_H
#define SEMESTRECONTROLLER_H

#include <QObject>
#include "model/semestre.h"
#include "model/etudiant.h"
#include "qsemestre.h"

class SemestreController : public QObject
{
		Q_OBJECT
	public:
		explicit SemestreController(Etudiant* etudiant, Semestre* semestre, QSemestre* qSemestre, QObject *parent = 0);
		void loadInfo();
	signals:
		void removed(Semestre *formation);
		void _removed();
	public slots:
		void remove();
		void edit();
	private:
		Etudiant* etudiant;
		Semestre* semestre;
		QSemestre* qSemestre;


		QString date();
};

#endif // SEMESTRECONTROLLER_H
