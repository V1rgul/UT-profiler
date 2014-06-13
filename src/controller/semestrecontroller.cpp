#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include "semestrecontroller.h"
#include "model/uv.h"

SemestreController::SemestreController(Semestre* semestre, QSemestre* qSemestre, QObject *parent) :
	QObject(parent), semestre(semestre), qSemestre(qSemestre)
{
	loadInfo();
}

void SemestreController::loadInfo(){
	QString date = QString("Annee");
	date.append(" ");
	date.append( (semestre->saison() == Semestre::AUTOMNE)? "A" : "P" );
	qSemestre->setDate(date);

	QStandardItemModel* model = new QStandardItemModel(2, semestre->uvs().size());
	int row = 0;
	foreach (QString uv, semestre->uvs().keys()){
		model->setItem(row, 0, new QStandardItem(uv));
		model->setItem(row, 1, new QStandardItem("42"));
		row++;
	}
	qSemestre->setTable(model);
}
