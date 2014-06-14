#ifndef QSEMESTREDIALOG_H
#define QSEMESTREDIALOG_H

#include <QDialog>
#include <QString>
#include "ui_qsemestredialog.h"
#include "quvchoisie.h"

class QSemestreDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit QSemestreDialog(QWidget *parent = 0);
		void setSaison(QString s);
		void setYear(int year);
		void addUVChoisie(QUVChoisie* uvChoisie);
		QFiltreBranche* getFiltreBranche();
		QAbstractItemModel* swapModel(QAbstractItemModel *model);
	signals:
		void saisonChanged();
		void yearChanged(int year);
	public slots:
		void saisonClicked();
		void spinYearChanged(int year);
	private:
		Ui::QSemestreDialog ui;
};

#endif // QSEMESTREDIALOG_H
