#ifndef QSEMESTRE_H
#define QSEMESTRE_H

#include <QWidget>
#include <QAbstractItemModel>
#include "ui_qsemestre.h"

class QSemestre : public QWidget
{
		Q_OBJECT
	public:
		explicit QSemestre(QWidget *parent = 0);

		void setDate(QString d);
		QAbstractItemModel* swapModel(QAbstractItemModel * model);
	signals:
		void editClicked();
		void deleteClicked();
	public slots:
		void buttonEditClicked();
		void buttonDeleteClicked();
	private:
		Ui::QSemestre ui;

};

#endif // QSEMESTRE_H
