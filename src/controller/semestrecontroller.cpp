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
	foreach (QString uv, semestre->uvs().keys()){
		model->setItem(0, column, new QStandardItem(uv));
		model->setItem(1, column, new QStandardItem("42"));
		column++;
	}
	QAbstractItemModel* old = qSemestre->swapModel(model);
	delete old;
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
	SemestreDialogController* c = new SemestreDialogController(etudiant, semestre, qSemestre);
	connect(c, SIGNAL(updated()), this, SLOT(update()));
}
