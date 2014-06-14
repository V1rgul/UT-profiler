#ifndef SEMESTREDIALOGCONTROLLER_H
#define SEMESTREDIALOGCONTROLLER_H

#include <QObject>
#include "qsemestredialog.h"
#include "model/etudiant.h"
#include "model/semestre.h"

class SemestreDialogController : public QObject
{
		Q_OBJECT
	public:
		SemestreDialogController(Etudiant* etudiant, Semestre* semestre, QWidget* parent=0);
	signals:
		void updated();
	public slots:
		void update();

		void saisonChanged();
		void yearChanged(int year);
		void filterChanged(QStringList list);
	private:
		Etudiant* etudiant;
		Semestre* semestre;
		QSemestreDialog* semestreDialog;
};

#endif // SEMESTREDIALOGCONTROLLER_H
