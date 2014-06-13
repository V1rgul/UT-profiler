#include <stdexcept>

#include "catalogue.h"
#include "uv.h"

const QString Catalogue::XML_NODE_NAME = "catalogue";

void Catalogue::ajouterUv (const UV& uv) {
  if (this->existe(uv.tag())) {
    throw std::invalid_argument("L'uv existe déjà");
  } 

  this->_uvs[uv.tag()] = uv;
}

void Catalogue::supprimerUv (const QString tag) {
  this->_uvs.remove(tag);
}

void Catalogue::editerUv (const QString oldTag, const UV& uv) {
  if (uv.tag() != oldTag) {
    if (this->existe(uv.tag())) {
      throw std::invalid_argument("L'uv existe déjà");
    }

    this->_uvs.remove(oldTag);
  } 

  this->_uvs[uv.tag()] = uv; 
}

bool Catalogue::existe(QString tag) {
  return this->_uvs.contains(tag);
}

QDomElement Catalogue::toXml () const {
  QDomDocument doc;
  QDomElement catalogue = doc.createElement(Catalogue::XML_NODE_NAME);
  
  QMap<QString, UV> uvs = this->uvs();
  QList<QString> keys = uvs.keys();

  for (int i = 0; i < keys.count(); i++) {
    catalogue.appendChild(uvs[keys[i]].toXml());
  }

  return catalogue;
}

void Catalogue::fromXml(const QDomNode& noeud) {
  if (noeud.nodeName() != Catalogue::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  QDomNodeList child = noeud.childNodes();

  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != UV::XML_NODE_NAME) {
      throw "Le catalogue ne peut contenir que des noeuds uv";
    }
    UV* uv = new UV();
    uv->fromXml(child.at(i));
    this->ajouterUv(*uv);
  }
}

Catalogue* Catalogue::charger () {
  QFile f(":/ressources/catalogue.xml");
  QDomDocument dom = QDomDocument("doc");
  QString err;

  if(!f.open(QIODevice::ReadOnly)) {
    throw "Impossible d'ouvrir le fichier catalogue.xml";
  }
  if (!dom.setContent(&f, &err)) {
    f.close();
    throw err;
  }

  QDomElement domElement = dom.documentElement();
  Catalogue *c = new Catalogue();
  c->fromXml(domElement);

  f.close();
  return c;
}

void Catalogue::sauvegarder () {
  QDomDocument doc;
  QFile f("catalogue-bis.xml");
  QString err;

  if(!f.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
    throw f.errorString();
  }

  doc.appendChild(doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'")); 
  doc.appendChild(this->toXml());

  QTextStream out(&f);
  //out << doc.toString();
  //qDebug() << doc.toString();

  f.close(); 
}

