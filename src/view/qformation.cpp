#include <QtDebug>
#include "qformation.h"
QFormation::QFormation(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.buttonAddSemestre, SIGNAL(clicked()), this, SLOT(buttonAddSemestreClicked()));
}


QFormation::QFormation(const QString &title, QWidget *parent) :
	QFormation(parent)
{
	ui.groupBox->setTitle(title);
}

void QFormation::addSemestre(QSemestre &semestre)
{
	ui.groupBox->layout()->addWidget(&semestre);
}



void QFormation::buttonAddSemestreClicked(){
	qDebug() << "click on addSemestre";
	emit addSemestreClicked();
}
