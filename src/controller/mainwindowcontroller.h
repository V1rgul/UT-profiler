#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>
#include <QApplication>
#include "mainwindow.h"
#include "quserdialog.h"
#include "model/etudiant.h"
#include "qformation.h"
#include <QStringList>

class MainWindowController : public QObject
{
	Q_OBJECT
	public:
		MainWindowController(QApplication &a, QObject *parent = 0);

	signals:

	public slots:
		void userSelect(const int index);
		void userSelectRejected();
		void nameChanged(const QString & name, const QString & surname);
		void addFormation();
		void removeFormation(FormationHorsUtc *formation);

		void exiting();
	private:
		QApplication *a;
		QUserDialog *userDialog;
		MainWindow *mainWindow;

		Etudiant *etudiant;
		QStringList etudiantList;

};

#endif // MAINWINDOWCONTROLLER_H
