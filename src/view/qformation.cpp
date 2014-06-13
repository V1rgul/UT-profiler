#include "qformation.h"
QFormation::QFormation(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
}


QFormation::QFormation(const QString &title, QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
}
