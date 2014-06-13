#include <iostream>
#include <QtXml>
#include <QFile>

#include "etudiant.h"

const QString Etudiant::XML_NODE_NAME = "etudiant";

QString Etudiant::nomFichier () const {
  return "./etudiant/" + this->nom() + "_" + this->prenom() + ".xml";
}

void Etudiant::ajouterFormation (Formation f) {
  this->_formations.append(f);
}

void Etudiant::supprimerFormation (int id) {
  for (int i = 0; i < this->_formations.count(); i++) {
    if (this->_formations[i].id() == id) {
      this->_formations.removeAt(i);
      return;
    }
  }
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

Etudiant* Etudiant::charger (const QString& nomComplet) {
  QStringList s = nomComplet.split(' ');
  return Etudiant::charger (s.at(0), s.at(1));
}

Etudiant* Etudiant::charger (const QString& nom, const QString& prenom) {
  Etudiant *e = new Etudiant();
  e->nom(nom);
  e->prenom(prenom);

  QFile f(e->nomFichier());
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
  e->fromXml(domElement);

  f.close();
  return e;
}

void Etudiant::sauvegarder () {
  if (this->nom().isEmpty() || this->prenom().isEmpty()) {
    throw QString("L'étudiant ne peut être sauvegardé sans nom et prénom");
  }

  QDir dir("./etudiant");
  if (!dir.exists()) {
    QDir().mkdir("./etudiant");
  }
  QDomDocument doc;
  QFile f(this->nomFichier());
  QString err;

  if(!(f.open(QIODevice::ReadWrite | QIODevice::Truncate))) {
    throw f.errorString();
  }

  doc.appendChild(doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'")); 
  doc.appendChild(this->toXml());

  QTextStream out(&f);
  out << doc.toString();

  f.close(); 
}

QStringList Etudiant::listeEtudiants () {
  QStringList fichiers = QDir("./etudiant").entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (int i = 0; i < fichiers.count(); i++) {
    fichiers[i] = fichiers[i].replace('_', ' ');
    fichiers[i].resize(fichiers[i].length() - 4);
  }

  return fichiers;
}
