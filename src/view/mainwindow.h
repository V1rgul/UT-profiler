#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qformation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void setName(const QString &name, const QString &surname);
	void addFormation(QFormation &formation);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
