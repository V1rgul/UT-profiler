#ifndef QSEMESTREDIALOG_H
#define QSEMESTREDIALOG_H

#include <QDialog>
#include "ui_qsemestredialog.h"

class QSemestreDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit QSemestreDialog(QWidget *parent = 0);

	private:
		Ui::QSemestreDialog ui;
};

#endif // QSEMESTREDIALOG_H
