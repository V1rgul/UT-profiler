#include "quserdialog.h"

QUserDialog::QUserDialog(const QStringList &userList, QWidget *parent) :
	QDialog(parent), model(userList)
{
	ui.setupUi(this);
	ui.comboBox->setModel(&model);
	connect(ui.buttonSelect, SIGNAL(clicked()), this, SLOT(buttonSelect()));
	connect(ui.buttonCreate, SIGNAL(clicked()), this, SLOT(buttonCreate()));
}

QUserDialog::QUserDialog(QWidget *parent) :
	QUserDialog(QStringList(), parent)
{	
}

void QUserDialog::buttonSelect()
{
	emit(selected(ui.comboBox->currentIndex()));
	setResult(QDialog::Accepted);
}

void QUserDialog::buttonCreate()
{
	emit(selected(-1));
	setResult(QDialog::Accepted);
}
