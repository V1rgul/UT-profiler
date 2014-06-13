#ifndef QFORMATION_H
#define QFORMATION_H

#include <QGroupBox>
#include "ui_qformation.h"

class QFormation : public QWidget
{
		Q_OBJECT
	public:
		explicit QFormation(QWidget *parent = 0);
		QFormation(const QString &title, QWidget *parent = 0);
	signals:

	public slots:


	private:
		Ui::QFormation ui;
};

#endif // QFORMATION_H
