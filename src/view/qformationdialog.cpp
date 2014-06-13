#include "qformationdialog.h"

QFormationDialog::QFormationDialog(QWidget *parent) :
    QDialog(parent)
{
	ui.setupUi(this);
}

void QFormationDialog::name(QString name){
	ui.editName->setText(name);
}
QString QFormationDialog::name(){
	return ui.editName->text();
}

void QFormationDialog::utc(boolean utc){
	ui.checkBoxUTC->setChecked(utc);
}
boolean QFormationDialog::utc(){
	return (ui.checkBoxUTC->checkState()==Qt::Checked);
}
