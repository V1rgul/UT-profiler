#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setName(const QString &name, const QString &surname){
	ui->editNom->setText(name);
	ui->editPrenom->setText(surname);
}

void MainWindow::addFormation(QFormation& formation){
	ui->tabEtudiant->layout()->addWidget(&formation);
}
