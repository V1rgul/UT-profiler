#include <iostream>
#include <QtXml>
#include <QFile>

#include "etudiant.h"

QString* Etudiant::nomFichier () {
  return new QString(this->nom() + "_" + this->prenom() + ".xml");
}

QFile* Etudiant::fichier (QIODevice::OpenMode mode) {
  QFile *f = new QFile(*(this->nomFichier()));

  if(!f->open(mode)) {
    return NULL;
  }

  return f; 
}

void Etudiant::sauvegarder () {
  QDomDocument *dom = new QDomDocument("doc");
  QFile *f;

  if(!(f = this->fichier(QIODevice::ReadWrite | QIODevice::Truncate))) {
    throw "Etudiant::sauvegarder: Impossible d'ouvrir le fichier";
  }
  if (!dom->setContent(f)) {
    f->close();
    throw "Etudiant::sauvegarder: Impossible d'associer le fichier à l'objet DOM";
  }
  f->close(); 
}
