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
	QString saison = (semestre->saison() == Semestre::AUTOMNE)? "A" : "P";
	qSemestre->setDate(QString() << "Annee" << "" << saison);

	QStandardItemModel* model = new QStandardItemModel();
	int row = 0;
	foreach (UV &uv, semestre->uvs.keys()){
		model->setData(row, 0, QStandardItem(uvs.value(uv)));
		model->setData(row, 1, QStandardItem("42"));
		row++;
	}
	qSemestre->setTable(model);
}
