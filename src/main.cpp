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

  const Catalogue* c = Catalogue::instance();

  Etudiant::listeEtudiants();
  Etudiant::creditsNecessaires();

  Etudiant e;
  e.nom("Potter");
  e.prenom("Harry");

  Semestre s1, s2;
  UVEtudiant uv1(*((*c)["NF16"])), 
             uv2(*((*c)["MB11"]));

  uv1.note("B");
  uv2.note("FX");

  s1.saison(Semestre::PRINTEMPS);

  s1.ajouterUv(&uv1);
  s1.ajouterUv(&uv2);

  e.formationUtc()->ajouterSemestre(&s1);
  e.formationUtc()->ajouterSemestre(&s2);

  FormationHorsUtc f1, f2;
  f1.nom("DUT Informatique");
  f1.credits(120);
  f2.nom("Semestre USA");
  f2.credits(30);

  e.ajouterFormation(&f1);
  e.ajouterFormation(&f2);

  QMap<QString, unsigned int> creditsNecessaires = Etudiant::creditsNecessaires();
  QMap<QString, unsigned int> credits = e.credits();

  for (int i = 0; i < creditsNecessaires.keys().count(); i++) {
    QString type = creditsNecessaires.keys()[i];
    qDebug() << type + ": " + QString::number(credits[type]) + "/" + QString::number(creditsNecessaires[type]);
  }

  try {
    e.sauvegarder(); // test la sauvegarde d'un etudiant dans un fichier xml
    Etudiant *e1 = Etudiant::charger("Newton Isaac"); // ainsi que le chargement d'un fichier xml
    qDebug() << "nom: " << e1->nom() << " prenom: " << e1->prenom();
  }
  //TODO: Ameliorer la gestion d'erreur
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


  MainWindowController mainWindowController(a);
  Q_UNUSED(mainWindowController);

  return a.exec();
}
