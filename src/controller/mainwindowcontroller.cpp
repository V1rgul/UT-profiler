#include <QtDebug>
#include "mainwindowcontroller.h"

MainWindowController::MainWindowController(QApplication& a, QObject *parent):
	QObject(parent), a(&a), mainWindow(new MainWindow())
{
	userDialog = new QUserDialog();
	connect(userDialog, SIGNAL(selected(int)), this, SLOT(userSelect(int)));
	connect(userDialog, SIGNAL(rejected()), this, SLOT(userSelectRejected()));
	userDialog->show();



	/*
	QFormation formation1("Test Formation");
	w.addFormation(formation1);

	QSemestre semestre1;
	formation1.addSemestre(semestre1);
	*/
}


void MainWindowController::userSelect(int index){
	qDebug() << "User selected:" << index;

	delete userDialog;
	userDialog = 0;

	mainWindow->show();
}
void MainWindowController::userSelectRejected(){
	qDebug() << "User select rejected";
	a->exit();
}
