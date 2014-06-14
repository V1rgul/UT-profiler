#include "semestredialogcontroller.h"
#include <QtDebug>
#include "model/uv.h"

SemestreDialogController::SemestreDialogController(Etudiant* etudiant, Semestre* semestre, QWidget* parent) :
	QObject(parent), etudiant(etudiant), semestre(semestre), semestreDialog(new QSemestreDialog), uvModel()
{
	update();
	filterChanged(QStringList());
	//* Test
	semestreDialog->getFiltreBranche()->addBranches(QStringList() << "_TC" << "_GI" << "_GM");
	//*/
	connect(semestreDialog, SIGNAL(saisonChanged()), this, SLOT(saisonChanged()));
	connect(semestreDialog, SIGNAL(yearChanged(int)), this, SLOT(yearChanged(int)));
	connect(semestreDialog->getFiltreBranche(), SIGNAL(filterChanged(QStringList)), this, SLOT(filterChanged(QStringList)));
	connect(this, SIGNAL(updated()), this, SLOT(update()));

	connect(semestreDialog, SIGNAL(rejected()), this, SLOT(deleteLater()));
	connect(semestreDialog, SIGNAL(rejected()), semestreDialog, SLOT(deleteLater()));	
}

void SemestreDialogController::update(){
	//Don't forget to empty things


	semestreDialog->setSaison( (semestre->saison()==Semestre::AUTOMNE)? QString("A") : QString("P") );
	semestreDialog->setYear(semestre->annee());
}

void SemestreDialogController::saisonChanged(){
	Semestre::Saison newSaison = (semestre->saison()==Semestre::AUTOMNE)? Semestre::PRINTEMPS : Semestre::AUTOMNE;
	semestre->saison( newSaison );
	emit(updated());
}
void SemestreDialogController::yearChanged(int year){
	semestre->annee(year);
	//qDebug() << "semestre->annee(" << QString::number(year) << ")";
	emit(updated());
}

void SemestreDialogController::filterChanged(QStringList list){
	qDebug() << "filterChanged(" << list.join(", ") << ")";

	QList<const UV*> uvs = etudiant->uvTriees(semestre->saison(), (list.count()==0)?0:&list );
	QStandardItemModel* model = new QStandardItemModel(list.count(), 1, this);

	int row = 0;
	foreach(const UV* uv, uvs){
		model->setItem(row, 0, new QStandardItem(uv->tag()));
		row++;
	}

	QAbstractItemModel* old = semestreDialog->swapModel(model);
	delete old;
}




