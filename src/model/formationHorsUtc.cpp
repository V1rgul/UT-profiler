#include <QMap>
#include <QtXml>
#include "formationHorsUtc.h"

const QString FormationHorsUtc::XML_NODE_NAME = "formation-hors-utc";

void FormationHorsUtc::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != FormationHorsUtc::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
  this->credits(e.attribute("credits").toInt());
}

QDomElement FormationHorsUtc::toXml () const {
  QDomDocument doc;
  QDomElement formation = doc.createElement(FormationHorsUtc::XML_NODE_NAME);

  formation.setAttribute("nom", this->nom());
  formation.setAttribute("credits", QString::number(this->credits()));

  return formation;
}


