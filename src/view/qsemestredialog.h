#ifndef QSEMESTREDIALOG_H
#define QSEMESTREDIALOG_H

#include <QDialog>
#include <QString>
#include "ui_qsemestredialog.h"

class QSemestreDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit QSemestreDialog(QWidget *parent = 0);
		void setSaison(QString s);
		QFiltreBranche* getFiltreBranche();
	signals:
		void saisonChanged();
	public slots:
		void saisonClicked();

	private:
		Ui::QSemestreDialog ui;
};

#endif // QSEMESTREDIALOG_H
