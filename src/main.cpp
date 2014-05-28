#include "view/mainwindow.h"
#include <QApplication>
#include <QMessageBox>

#include "model/etudiant.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Etudiant e;
    e.nom("Dupont");
    e.prenom("Jean");

    try {
      e.sauvegarder();
    } catch (const char* e) {
      QMessageBox box;
      box.setIcon(QMessageBox::Critical);
      box.setText(e);
      box.exec();
    }

    return a.exec();
}
