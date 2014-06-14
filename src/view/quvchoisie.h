#ifndef QUVCHOISIE_H
#define QUVCHOISIE_H

#include <QWidget>
#include "ui_quvchoisie.h"

class QUVChoisie : public QWidget
{
		Q_OBJECT

	public:
		explicit QUVChoisie(QWidget *parent = 0);
		void setName(QString s);

	signals:
		void removeClicked();
	public slots:
		void buttonRemoveClicked();
	private:
		Ui::QUVChoisie ui;
};

#endif // QUVCHOISIE_H
