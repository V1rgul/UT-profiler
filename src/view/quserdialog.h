#ifndef QUSER_H
#define QUSER_H

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
	public slots:
		void buttonSelect();
		void buttonCreate();
	private:
		Ui::QUserDialog ui;
		QStringListModel model;
};

#endif // QUSER_H
