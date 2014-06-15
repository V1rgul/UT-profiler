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

		void edit(QString name, int creditsCS, int creditsTM, int creditsTSH);
	signals:
		void remove();
		void edited(QString name, int creditsCS, int creditsTM, int creditsTSH);
	public slots:
		void buttonRemoveClicked();
		void editedName(QString name);
		void editedCredits(int credits);
	private:
		Ui::QFormation ui;
};

#endif // QFORMATION_H
