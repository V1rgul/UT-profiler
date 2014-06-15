#include <QtDebug>
#include "qformation.h"

QFormation::QFormation(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.buttonDelete, SIGNAL(clicked()), this, SLOT(buttonRemoveClicked()));
	connect(ui.editName, SIGNAL(textChanged(QString)), this, SLOT(editedName(QString)));
	connect(ui.spinCreditsCS, SIGNAL(valueChanged(int)), this, SLOT(editedCredits(int)));
	connect(ui.spinCreditsTM, SIGNAL(valueChanged(int)), this, SLOT(editedCredits(int)));
	connect(ui.spinCreditsTSH, SIGNAL(valueChanged(int)), this, SLOT(editedCredits(int)));
}


void QFormation::edit(QString name, int creditsCS, int creditsTM, int creditsTSH){
	ui.editName->setText(name);
	ui.spinCreditsCS->setValue(creditsCS);
	ui.spinCreditsTM->setValue(creditsTM);
	ui.spinCreditsTSH->setValue(creditsTSH);
}

void QFormation::buttonRemoveClicked(){
	emit(remove());
}

void QFormation::editedName(QString name){
	emit(edited(name, ui.spinCreditsCS->value(), ui.spinCreditsTM->value(), ui.spinCreditsTSH->value()));
}
void QFormation::editedCredits(int credits){
	emit(edited(ui.editName->text(), ui.spinCreditsCS->value(), ui.spinCreditsTM->value(), ui.spinCreditsTSH->value()));
}
