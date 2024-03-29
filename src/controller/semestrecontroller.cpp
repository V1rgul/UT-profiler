#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include <QMessageBox>
#include "semestrecontroller.h"
#include "model/uv.h"
#include "semestredialogcontroller.h"

SemestreController::SemestreController(Etudiant* etudiant, Semestre* semestre, QSemestre* qSemestre, QObject *parent) :
	QObject(parent), etudiant(etudiant), semestre(semestre), qSemestre(qSemestre)
{
	connect(this, SIGNAL(_removed()), qSemestre, SLOT(deleteLater()));
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));
	connect(qSemestre, SIGNAL(deleteClicked()), this, SLOT(remove()));
	connect(qSemestre, SIGNAL(editClicked()), this, SLOT(edit()));


	update();
}

void SemestreController::update(){

	qSemestre->setDate(date());

	QStandardItemModel* model = new QStandardItemModel(2, semestre->uvs().size(), this);
	int column = 0;
	foreach (UVEtudiant* uv, semestre->uvs().values()){
		QStandardItem* tag = new QStandardItem(uv->tag());
		tag->setEditable(false);
		QStandardItem* note = new QStandardItem(uv->note());
		note->setEditable(false);

		model->setItem(0, column, tag);
		model->setItem(1, column, note);
		column++;
	}
	QAbstractItemModel* old = qSemestre->swapModel(model);
	delete old;

	emit(updated());
}

QString SemestreController::date(){
	QString date = QString::number(semestre->annee());
	date.append(" ");
	date.append( (semestre->saison() == Semestre::AUTOMNE)? "A" : "P" );
	return date;
}

void SemestreController::remove(){
	QString text("Etes vous sur de vouloir supprimmer le Semestre ");
	text.append(date());
	QMessageBox::StandardButton b = QMessageBox::warning( qSemestre,
									  QString("Attention"),
									  text,
									  QMessageBox::Yes | QMessageBox::Discard);
	if(b == QMessageBox::Yes){
		emit(removed(semestre));
		emit(_removed());
	}
}

void SemestreController::edit(){
	SemestreDialogController* c = new SemestreDialogController(etudiant, semestre, this);
	connect(c, SIGNAL(updated()), this, SLOT(update()));
}
