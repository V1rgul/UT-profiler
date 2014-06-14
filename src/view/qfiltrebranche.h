#ifndef QFILTREBRANCHE_H
#define QFILTREBRANCHE_H

#include <QWidget>
#include <QSemaphore>
#include "ui_qfiltrebranche.h"

class QFiltreBranche : public QWidget
{
		Q_OBJECT

	public:
		explicit QFiltreBranche(QWidget *parent = 0);
		void addBranches(QStringList &listeBranches);
	signals:
		void filterChanged(QStringList);
	public slots:
		void allToggled(bool v);
		void checkBox(bool v);

	private:
		Ui::QFiltreBranche ui;
		QSemaphore sem; // :)
};

#endif // QFILTREBRANCHE_H
