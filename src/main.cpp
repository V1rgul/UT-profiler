#include "view/mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>

#include "model/etudiant.h"
#include "model/formation.h"
#include "model/semestre.h"
#include "model/uvEtudiant.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  Etudiant e;
  e.nom("Dupont");
  e.prenom("Jean");

  Formation f;
  Semestre s1, s2;
  UVEtudiant uv1, uv2, uv3, uv4, uv5, uv6;

  uv1.tag("MB11");
  uv2.tag("NF16");
  uv3.tag("SR01");
  uv4.tag("LO21");
  uv5.tag("NF17");
  uv6.tag("SR02");
  //uv.note(EN_COURS);

  s1.ajouterUv(uv1);
  s1.ajouterUv(uv2);
  s1.ajouterUv(uv3);
  s2.ajouterUv(uv4);
  s2.ajouterUv(uv5);
  s2.ajouterUv(uv6);

  f.ajouterSemestre(s1);
  f.ajouterSemestre(s2);

  e.ajouterFormation(f);

  try {
    e.sauvegarder(); // test la sauvegarde d'un etudiant dans un fichier xml
    Etudiant *e1 = Etudiant::charger("../test.xml"); // ainsi que le chargement d'un fichier xml
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
  }

  return a.exec();
}
