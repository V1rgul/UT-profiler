#include "qsemestredialog.h"
#include "ui_qsemestredialog.h"

QSemestreDialog::QSemestreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSemestreDialog)
{
	ui->setupUi(this);
}

QSemestreDialog::~QSemestreDialog()
{
	delete ui;
}
