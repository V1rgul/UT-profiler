#ifndef QFORMATION_H
#define QFORMATION_H

#include <QGroupBox>
#include "qsemestre.h"
#include "ui_qformation.h"

class QFormation : public QWidget
{
		Q_OBJECT
	public:
		explicit QFormation(QWidget *parent = 0);
		QFormation(const QString &title, QWidget *parent = 0);

		void addSemestre(QSemestre &semestre);
	signals:
		void addSemestreClicked();
	public slots:
		void buttonAddSemestreClicked();

	private:
		Ui::QFormation ui;
};

#endif // QFORMATION_H
