#include <stdexcept>
#include <QList>
#include <QtXml>

#include "equivalence.h"

const QString Equivalence::XML_NODE_NAME = "equivalence";
int Equivalence::idCpt = 0;

void Equivalence::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != Equivalence::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    QDomNode c = child.at(i);
    if (c.nodeName() != UV::CREDIT_XML_NODE_NAME) {
      throw "Les noeuds equivalence ne peuvent contenir que des balise credits";
    }
    QDomElement e = c.toElement();
    QString type = e.attribute("type");
    this->_credits[type] = e.text().toInt();
  }
}

QDomElement Equivalence::toXml () const {
  QDomDocument doc;
  QDomElement e = doc.createElement(Equivalence::XML_NODE_NAME);
  QDomElement creditsElem = doc.createElement(UV::CREDIT_XML_NODE_NAME);

  e.setAttribute("nom", this->nom());

  QMap<QString, unsigned int> credits = this->credits();
  QList<QString> keys = credits.keys();

  for (int i = 0; i < keys.count(); i++) {
    QDomText nombreCredits = doc.createTextNode(QString::number(credits[keys[i]]));
    creditsElem.setAttribute("type", keys[i]);
    creditsElem.appendChild(nombreCredits);
    e.appendChild(creditsElem);
  }

  return e;
}
