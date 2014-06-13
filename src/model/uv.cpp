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
    QDomNode c = child.at(i);
    if (c.nodeName() != UV::CREDIT_XML_NODE_NAME) {
      throw "Les uv ne peuvent contenir que des balises credits";
    }
    QDomElement e = c.toElement();
    QString type = e.attribute("type");
    this->_credits[type] = e.text().toInt();
  }
}

QDomElement UV::toXml () const {
  QDomDocument doc;
  QDomElement e = doc.createElement(UV::XML_NODE_NAME);
  QDomElement creditsElem = doc.createElement(UV::CREDIT_XML_NODE_NAME);

  e.setAttribute("tag", this->tag());
  e.setAttribute("titre", this->titre());
  e.setAttribute("cursus", this->cursus().join(" "));
  if (this->automne()) { e.setAttribute("automne", "automne"); }
  if (this->printemps()) { e.setAttribute("printemps", "printemps"); }

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

QString UV::toString () {
  QString ret = 
        this->tag() + " - " + this->titre() + "\n"
          + "\tcursus: " + this->cursus().join(" ") + "\n"
          + "\tautomne: " + (this->automne() ? "true" : "false") + "\n"
          + "\tprintemps: " + (this->printemps() ? "true" : "false") + "\n"
          + "\tcredits: " + "\n";

  QMap<QString, unsigned int> credits = this->credits();
  QList<QString> keys = credits.keys();

  for (int i = 0; i < keys.count(); i++) {
    ret += "\t\t" + keys[i] + ": " + QString::number(credits[keys[i]]) + "\n";
  }

  return ret;
}
