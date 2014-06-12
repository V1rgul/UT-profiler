#include "uv.h"

const QString UV::XML_NODE_NAME = "uv";

void UV::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != UV::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }
  
  QDomElement e = noeud.toElement();
  this->tag(e.attribute("tag"));
  this->titre(e.attribute("titre"));
  this->credits(e.attribute("credits").toInt());
  this->automne(e.hasAttribute("automne"));
  this->printemps(e.hasAttribute("printemps"));
  this->cursus(e.attribute("cursus").split(' '));
}

QDomElement UV::toXml () const {
  QDomDocument doc;
  QDomElement e = doc.createElement(UV::XML_NODE_NAME);

  e.setAttribute("tag", this->tag());
  e.setAttribute("titre", this->titre());
  e.setAttribute("credits", this->credits());
  e.setAttribute("cursus", this->cursus().join(" "));
  if (this->automne()) { e.setAttribute("automne", "automne"); }
  if (this->printemps()) { e.setAttribute("printemps", "printemps"); }

  return e;
}
