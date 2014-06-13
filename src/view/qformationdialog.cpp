#include <QtDebug>
#include "qformationdialog.h"

QFormationDialog::QFormationDialog(QWidget *parent) :
    QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(buttonAccepted()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(buttonRejected()));
}

void QFormationDialog::name(QString name){
	ui.editName->setText(name);
}
QString QFormationDialog::name(){
	return ui.editName->text();
}

void QFormationDialog::utc(bool utc){
	ui.checkBoxUTC->setChecked(utc);
}
bool QFormationDialog::utc(){
	return (ui.checkBoxUTC->checkState()==Qt::Checked);
}

void QFormationDialog::buttonAccepted(){
	qDebug() << "accepted";
	emit(finished(QDialog::Accepted));
}
void QFormationDialog::buttonRejected(){
	qDebug() << "rejected";
	emit(finished(QDialog::Rejected));
}
