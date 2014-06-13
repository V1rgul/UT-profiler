#include <QtDebug>
#include "qformation.h"

QFormation::QFormation(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.buttonDelete, SIGNAL(clicked()), this, SLOT(buttonRemoveClicked()));
	connect(ui.editName, SIGNAL(textChanged(QString)), this, SLOT(editedName(QString)));
	connect(ui.spinCredits, SIGNAL(valueChanged(int)), this, SLOT(editedCredits(int)));
}


void QFormation::edit(QString name, int credits){
	ui.editName->setText(name);
	ui.spinCredits->setValue(credits);
}

void QFormation::buttonRemoveClicked(){
	emit(remove());
}

void QFormation::editedName(QString name){
	emit(edited(name, ui.spinCredits->value()));
}
void QFormation::editedCredits(int credits){
	emit(edited(ui.editName->text(), credits));
}
