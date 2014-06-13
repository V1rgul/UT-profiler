#include "view/mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>

#include "model/catalogue.h"
#include "model/uv.h"
#include "model/etudiant.h"
#include "model/formation.h"
#include "model/semestre.h"
#include "model/uvEtudiant.h"

#include "view/qformation.h"
#include "view/qsemestre.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  Catalogue* c;
  try {
    c = Catalogue::charger();
  } catch (const char* e) {
    qDebug() << e;
  }

  return a.exec();
}
