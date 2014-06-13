#ifndef QUSERDIALOG_H
#define QUSERDIALOG_H

#include <QDialog>
#include<QStringList>
#include<QStringListModel>
#include "ui_quserdialog.h"

class QUserDialog : public QDialog
{
		Q_OBJECT

	public:
		QUserDialog(const QStringList &userList, QWidget *parent = 0);
		explicit QUserDialog(QWidget *parent = 0);
	signals:
		//-1 for new, id of selected user in userList else
		void selected(int index);

		void doneEvent(int r);
	public slots:
		void buttonSelect();
		void buttonCreate();
	private:
		Ui::QUserDialog ui;
		QStringListModel model;
};

#endif // QUSERDIALOG_H
