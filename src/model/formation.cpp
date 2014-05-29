#include <QtXml>
#include "formation.h"

const QString Formation::XML_NODE_NAME = "formation";

void Formation::ajouterSemestre (Semestre s) {
  this->_semestres.append(s);
}

void Formation::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != Formation::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != Semestre::XML_NODE_NAME) {
      throw "Les noeuds formation ne peuvent contenir que des noeuds semestre";
    }
    Semestre *s = new Semestre();
    s->fromXml(child.at(i));
    this->ajouterSemestre(*s);
  }
}

QDomElement Formation::toXml () const {
  QDomDocument doc;
  QDomElement formation = doc.createElement(Formation::XML_NODE_NAME);

  for (int i = 0; i < this->semestres().count(); i++) {
    formation.appendChild(this->semestres()[i].toXml());
  }

  return formation;
}

