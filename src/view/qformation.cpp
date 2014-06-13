#include <QtDebug>
#include "qformation.h"

QFormation::QFormation(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.buttonAddSemestre, SIGNAL(clicked()), this, SLOT(buttonAddSemestreClicked()));
}

void QFormation::addSemestre(QSemestre &semestre)
{
	ui.groupBox->layout()->addWidget(&semestre);
}
void QFormation::name(QString name){
	ui.groupBox->setTitle(name);
}



void QFormation::buttonAddSemestreClicked(){
	qDebug() << "click on addSemestre";
	emit addSemestreClicked();
}
