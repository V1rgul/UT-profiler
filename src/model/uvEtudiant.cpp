#include <QtXml>

#include "uvEtudiant.h"

const QString UVEtudiant::XML_NODE_NAME = "uv";

QSet<QString> UVEtudiant::listeNotes () {
  QSet<QString> set;
  set.insert("A");
  set.insert("B");
  set.insert("C");
  set.insert("D");
  set.insert("E");
  set.insert("F");
  set.insert("FX");
  set.insert("ABS");

  return set;
}

void UVEtudiant::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != UVEtudiant::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }
  
  QDomElement e = noeud.toElement();
  this->tag(e.attribute("tag"));
  //this->note(e.attribute("note"));
}

QDomElement UVEtudiant::toXml () const {
  QDomDocument doc;
  QDomElement e = doc.createElement(UVEtudiant::XML_NODE_NAME);

  e.setAttribute("tag", this->tag());
  e.setAttribute("note", this->note());

  return e;
}
