#include <QtXml>

#include "catalogue.h"
#include "uvEtudiant.h"

/**
 * @brief Nom du noeud XML correspondant à une uv 
 */
const QString UVEtudiant::XML_NODE_NAME = "uv";

QList<QString> UVEtudiant::listeNotes () {
  QList<QString> set;
  set.append("-");
  set.append("A");
  set.append("B");
  set.append("C");
  set.append("D");
  set.append("E");
  set.append("F");
  set.append("FX");
  set.append("ABS");

  return set;
}

void UVEtudiant::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != UVEtudiant::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }
  
  QDomElement e = noeud.toElement();
  this->_details = (*(Catalogue::instance()))[e.attribute("tag")];
  this->note(e.attribute("note"));
}

QDomElement UVEtudiant::toXml () const {
  QDomDocument doc;
  QDomElement e = doc.createElement(UVEtudiant::XML_NODE_NAME);

  e.setAttribute("tag", this->tag());
  e.setAttribute("note", this->note());

  return e;
}
