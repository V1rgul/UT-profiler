#ifndef QSEMESTRE_H
#define QSEMESTRE_H

#include <QWidget>
#include "ui_qsemestre.h"

class QSemestre : public QWidget
{
		Q_OBJECT
	public:
		explicit QSemestre(QWidget *parent = 0);

	signals:

	public slots:

	private:
		Ui::QSemestre ui;

};

#endif // QSEMESTRE_H
