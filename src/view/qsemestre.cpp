#include "qsemestre.h"

QSemestre::QSemestre(QWidget *parent) :
    QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.buttonEdit, SIGNAL(clicked()), this, SLOT(buttonEditClicked()));
	connect(ui.buttonDelete, SIGNAL(clicked()), this, SLOT(buttonDeleteClicked()));
}

void QSemestre::setDate(QString d){
	ui.labelDate->setText(d);
}

void QSemestre::buttonEditClicked(){
	emit(editClicked());
}

void QSemestre::buttonDeleteClicked(){
	emit(deleteClicked());
}

QAbstractItemModel* QSemestre::swapModel(QAbstractItemModel *model){
	QAbstractItemModel *old = ui.tableUV->model();
	ui.tableUV->setModel(model);
	return old;
}
