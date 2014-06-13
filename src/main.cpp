#include <QApplication>
#include <QMessageBox>
#include <iostream>

#include "model/catalogue.h"
#include "model/uv.h"
#include "model/etudiant.h"
#include "model/formation.h"
#include "model/semestre.h"
#include "model/uvEtudiant.h"

#include "controller/mainwindowcontroller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);


  /*Catalogue* c;
  try {
    c = Catalogue::charger();
  } catch (const char* e) {
    qDebug() << e;
  }

  Etudiant e;
  e.nom("Stevie");
  e.prenom("Wonder");

  Formation f;
  Semestre s1, s2;
  UVEtudiant uv1, uv2, uv3, uv4, uv5, uv6;

  uv1.tag("PS91"); uv1.note("B");
  uv2.tag("PH09"); uv2.note("FX");
  uv3.tag("NF24"); uv3.note("C");
  uv4.tag("SA11"); uv4.note("A");
  uv5.tag("LG30");
  uv6.tag("MC05");

  s1.ajouterUv(&uv1);
  s1.ajouterUv(&uv2);
  s1.ajouterUv(&uv3);
  s2.ajouterUv(&uv4);
  s2.ajouterUv(&uv5);
  s2.ajouterUv(&uv6);

  f.ajouterSemestre(&s1);
  f.ajouterSemestre(&s2);

  e.ajouterFormation(f);

  try {
    e.sauvegarder();  //test la sauvegarde d'un etudiant dans un fichier xml
    Etudiant *e1 = Etudiant::charger("Abou Baker"); // ainsi que le chargement d'un fichier xml
    qDebug() << "nom: " << e1->nom() << " prenom: " << e1->prenom();
  }
  // TODO: Ameliorer la gestion d'erreur
  catch (QString& e) {
    QMessageBox box;
    box.setIcon(QMessageBox::Critical);
    box.setText(e);
    box.exec();
  } catch (const char* e2) {
    QMessageBox box;
    box.setIcon(QMessageBox::Critical);
    box.setText(e2);
    box.exec();
  }*/


  MainWindowController mainWindowController(a);
  Q_UNUSED(mainWindowController);

  return a.exec();
}
