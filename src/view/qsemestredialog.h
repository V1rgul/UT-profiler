#ifndef QSEMESTREDIALOG_H
#define QSEMESTREDIALOG_H

#include <QDialog>

namespace Ui {
class QSemestreDialog;
}

class QSemestreDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit QSemestreDialog(QWidget *parent = 0);
		~QSemestreDialog();

	private:
		Ui::QSemestreDialog *ui;
};

#endif // QSEMESTREDIALOG_H
