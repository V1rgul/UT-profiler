#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include "quserdialog.h"

class MainWindowController : public QObject
{
	Q_OBJECT
	public:
		MainWindowController(QApplication &a, QObject *parent = 0);

	signals:

	public slots:
		void userSelect(int index);
		void userSelectRejected();
	private:
		QApplication *a;
		QUserDialog *userDialog;
		MainWindow *mainWindow;
};

#endif // MAINWINDOWCONTROLLER_H
