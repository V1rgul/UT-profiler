#include "qsemestredialog.h"
#include "ui_qsemestredialog.h"

QSemestreDialog::QSemestreDialog(QWidget *parent) :
	QDialog(parent), ui()
{
	ui.setupUi(this);
	connect(ui.buttonSaison, SIGNAL(clicked()), this, SLOT(saisonClicked()));
	connect(ui.spinAnnee, SIGNAL(valueChanged(int)), this, SLOT(spinYearChanged(int)));

	this->show();
}

QFiltreBranche* QSemestreDialog::getFiltreBranche(){
	return ui.filtreBranche;
}

QTableView* QSemestreDialog::getTableView(){
	return ui.listView;
}

void QSemestreDialog::saisonClicked(){
	emit(saisonChanged());
}

void QSemestreDialog::setSaison(QString s){
	ui.buttonSaison->setText(s);
}

void QSemestreDialog::spinYearChanged(int year){
	emit(yearChanged(year));
}

void QSemestreDialog::setYear(int year){
	ui.spinAnnee->setValue(year);
}

QAbstractItemModel* QSemestreDialog::swapModel(QAbstractItemModel *model){
	QAbstractItemModel *old = ui.listView->model();
	ui.listView->setModel(model);
	return old;
}

void QSemestreDialog::addUVChoisie(QUVChoisie* uvChoisie){
	ui.groupUVChoisies->layout()->addWidget(uvChoisie);
}
