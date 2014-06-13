#include "quserdialog.h"

QUserDialog::QUserDialog(const QStringList &userList, QWidget *parent) :
	QDialog(parent), model(userList)
{
	ui.setupUi(this);
	ui.comboBox->setModel(&model);
	connect(this, SIGNAL(doneEvent(int)), this, SLOT(done(int)));
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
	emit(doneEvent(QDialog::Accepted));
}

void QUserDialog::buttonCreate()
{
	emit(selected(-1));
	emit(doneEvent(QDialog::Accepted));
}
