#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include <QMessageBox>
#include "semestrecontroller.h"
#include "model/uv.h"

SemestreController::SemestreController(Semestre* semestre, QSemestre* qSemestre, QObject *parent) :
	QObject(parent), semestre(semestre), qSemestre(qSemestre)
{
	connect(this, SIGNAL(_removed()), qSemestre, SLOT(deleteLater()));
	connect(this, SIGNAL(_removed()), this, SLOT(deleteLater()));
	connect(qSemestre, SIGNAL(deleteClicked()), this, SLOT(remove()));


	loadInfo();
}

void SemestreController::loadInfo(){

	qSemestre->setDate(date());

	QStandardItemModel* model = new QStandardItemModel(2, semestre->uvs().size());
	int column = 0;
	foreach (QString uv, semestre->uvs().keys()){
		model->setItem(0, column, new QStandardItem(uv));
		model->setItem(1, column, new QStandardItem("42"));
		column++;
	}
	qSemestre->setTable(model);
}

QString SemestreController::date(){
	QString date = QString("Annee");
	date.append(" ");
	date.append( (semestre->saison() == Semestre::AUTOMNE)? "A" : "P" );
	return date;
}

void SemestreController::remove(){
	QString text("Etes vous sur de vouloir supprimmer le Semestre ");
	text.append(date());
	QMessageBox::StandardButton b = QMessageBox::warning( 0,
									  QString("Attention"),
									  text,
									  QMessageBox::Yes | QMessageBox::Discard);
	if(b == QMessageBox::Yes){
		emit(removed(semestre));
		emit(_removed());
	}
}
