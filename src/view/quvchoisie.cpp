#include "quvchoisie.h"
#include "ui_quvchoisie.h"

QUVChoisie::QUVChoisie(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.buttonUV, SIGNAL(clicked()), this, SLOT(buttonRemoveClicked()));
}

void QUVChoisie::buttonRemoveClicked(){
	emit(removeClicked());
}

void QUVChoisie::setName(QString s){
	ui.buttonUV->setText(s);
}
