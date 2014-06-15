#ifndef SEMESTREDIALOGCONTROLLER_H
#define SEMESTREDIALOGCONTROLLER_H

#include <QObject>
#include <QStandardItemModel>
#include "qsemestredialog.h"
#include "model/etudiant.h"
#include "model/semestre.h"
#include "model/uvEtudiant.h"
#include "qspinnerdelegate.h"
#include "qcheckboxdelegate.h"

class SemestreDialogController : public QObject
{
		Q_OBJECT
	public:
		SemestreDialogController(Etudiant* etudiant, Semestre* semestre, QObject* parent=0);
		~SemestreDialogController();

	signals:
		void updated();
	public slots:
		void update();

		void uvChoisieRemoved(UVEtudiant* uv);
		void saisonChanged();
		void yearChanged(int year);
		void filterChanged(QStringList list);
		void UVChanged(QStandardItem * item);
	private:
		Etudiant* etudiant;
		Semestre* semestre;
		QSemestreDialog* semestreDialog;
		QStringList currentFilter;


		QStandardItemModel* uvModel;
		QSpinnerDelegate* spinDelegate;
		QCheckBoxDelegate* checkDelegate;

		void updateList();
		void addUVChoisieToView(UVEtudiant* uv);
};

#endif // SEMESTREDIALOGCONTROLLER_H
