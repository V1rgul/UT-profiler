#include "uv.h"

const QString UV::XML_NODE_NAME = "uv";
const QString UV::CREDIT_XML_NODE_NAME = "credits";

void UV::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != UV::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }
  
  QDomElement e = noeud.toElement();
  this->tag(e.attribute("tag"));
  this->titre(e.attribute("titre"));
  this->automne(e.hasAttribute("automne"));
  this->printemps(e.hasAttribute("printemps"));
  this->cursus(e.attribute("cursus").split(' '));

  QDomNodeList child = noeud.childNodes();

  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != UV::CREDIT_XML_NODE_NAME) {
      throw "Les uv ne peuvent contenir des balises credits";
    }
    this->_credits[child.at(i).toElement().attribute("type")] = child.at(i).nodeValue().toInt();
  }
}

QDomElement UV::toXml () const {
  QDomDocument doc;
  QDomElement e = doc.createElement(UV::XML_NODE_NAME);
  QDomNode creditsNode;
  QDomElement creditsElem;

  e.setAttribute("tag", this->tag());
  e.setAttribute("titre", this->titre());
  e.setAttribute("cursus", this->cursus().join(" "));
  if (this->automne()) { e.setAttribute("automne", "automne"); }
  if (this->printemps()) { e.setAttribute("printemps", "printemps"); }

  QMap<QString, unsigned int> credits = this->credits();
  QList<QString> keys = credits.keys();

  qDebug() << this->tag() << ": " << keys.count() << " types de crédit";
  for (int i = 0; i < keys.count(); i++) {
    creditsNode.setNodeValue(QString::number(credits[keys[i]]));
    creditsElem = creditsNode.toElement();
    creditsElem.setTagName(UV::CREDIT_XML_NODE_NAME);
    qDebug() << "text: " << creditsElem.text();
    e.appendChild(creditsElem);
  }

  qDebug() << doc.toString();

  return e;
}

QString UV::toString () {
  QString ret = 
        this->tag() + " - " + this->titre() + "\n"
          + "\tautomne: " + this->automne() + "\n"
          + "\tprintemps: " + this->printemps() + "\n"
          + "\tcredits: " + "\n";

  QMap<QString, unsigned int> credits = this->credits();
  QList<QString> keys = credits.keys();

  for (int i = 0; i < keys.count(); i++) {
    ret += "\t\t" + keys[i] + ": " + credits[keys[i]] + "\n";
  }

  return ret;
}
