#include <QMap>
#include <QtXml>
#include "formationHorsUtc.h"

/**
 * @brief Nom du noeud XML correspondant à une formation hors utc
 */
const QString FormationHorsUtc::XML_NODE_NAME = "formation-hors-utc";

void FormationHorsUtc::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != FormationHorsUtc::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
  this->creditsCS(e.attribute("credits-cs").toInt());
  this->creditsTM(e.attribute("credits-tm").toInt());
  this->creditsTSH(e.attribute("credits-tsh").toInt());
}

QDomElement FormationHorsUtc::toXml () const {
  QDomDocument doc;
  QDomElement formation = doc.createElement(FormationHorsUtc::XML_NODE_NAME);

  formation.setAttribute("nom", this->nom());
  formation.setAttribute("credits-cs", QString::number(this->creditsCS()));
  formation.setAttribute("credits-tm", QString::number(this->creditsTM()));
  formation.setAttribute("credits-tsh", QString::number(this->creditsTSH()));

  return formation;
}


