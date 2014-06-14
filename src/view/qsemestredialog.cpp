#include "qsemestredialog.h"
#include "ui_qsemestredialog.h"

QSemestreDialog::QSemestreDialog(QWidget *parent) :
	QDialog(parent), ui()
{
	ui.setupUi(this);
	connect(ui.buttonSaison, SIGNAL(clicked()), this, SLOT(saisonClicked()));


	this->show();
}


void QSemestreDialog::saisonClicked(){
	emit(saisonChanged());
}

void QSemestreDialog::setSaison(QString s){
	ui.buttonSaison->setText(s);
}
