#ifndef QFORMATIONDIALOG_H
#define QFORMATIONDIALOG_H

#include <QDialog>
#include "ui_qformationdialog.h"

class QFormationDialog : public QDialog
{
		Q_OBJECT
	public:
		explicit QFormationDialog(QWidget *parent = 0);
		void name(QString name);
		QString name();
		void utc(boolean utc);
		boolean utc();
	signals:

	public slots:

	private:
		Ui::QFormationDialog ui;
};

#endif // QFORMATIONDIALOG_H
