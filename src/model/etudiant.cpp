#include <iostream>
#include <QtXml>
#include <QFile>

#include "etudiant.h"

const QString Etudiant::XML_NODE_NAME = "etudiant";

QString* Etudiant::nomFichier () const {
  return new QString(this->nom() + "_" + this->prenom() + ".xml");
}

QFile* Etudiant::fichier (QIODevice::OpenMode mode) const {
  QString* n = this->nomFichier();
  QFile *f = new QFile(*n);

  if(!f->open(mode)) {
    return NULL;
  }

  return f; 
}

void Etudiant::ajouterFormation (Formation f) {
  this->_formations.append(f);
}

QDomElement Etudiant::toXml () const {
  QDomDocument doc;
  QDomElement etudiant = doc.createElement(Etudiant::XML_NODE_NAME);
  etudiant.setAttribute("nom", this->nom());
  etudiant.setAttribute("prenom", this->prenom());
  
  for (int i = 0; i < this->formations().count(); i++) {
    etudiant.appendChild(this->formations()[i].toXml());
  }

  return etudiant;
}

void Etudiant::fromXml (QDomNode& noeud) {
  if (noeud.nodeName() != Etudiant::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
  this->prenom(e.attribute("prenom"));

  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != Formation::XML_NODE_NAME) {
      throw "Les noeuds etudiant ne peuvent contenir que des noeuds formation";
    }
    Formation *f = new Formation();
    f->fromXml(child.at(i));
    this->ajouterFormation(*f);
  }
}

Etudiant* Etudiant::charger (const QString& chemin) {
  QFile f(chemin);
  QDomDocument dom = QDomDocument("doc");
  QString err;

  if(!f.open(QIODevice::ReadOnly)) {
    throw "Etudiant::charger: Impossible d'ouvrir le fichier";
  }
  if (!dom.setContent(&f, &err)) {
    f.close();
    throw "Etudiant::charger: " + err;
  }

  QDomElement domElement = dom.documentElement();
  Etudiant *e = new Etudiant();
  e->fromXml(domElement);

  f.close();
  return e;
}

void Etudiant::sauvegarder () {
  QDomDocument doc;
  QFile *f;
  QString err;

  if(!(f = this->fichier(QIODevice::ReadWrite | QIODevice::Truncate))) {
    throw "Etudiant::sauvegarder: Impossible d'ouvrir le fichier";
  }

  doc.appendChild(doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'")); 
  doc.appendChild(this->toXml());

  QTextStream out(f);
  out << doc.toString();

  f->close(); 
}
