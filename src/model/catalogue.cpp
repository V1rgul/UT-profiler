#include "catalogue.h"
#include "uv.h"

const QString Catalogue::XML_NODE_NAME = "catalogue";

Catalogue* Catalogue::instance () {
  if (!Catalogue::_instance) { _instance = new Catalogue(); }
  return _instance;
}

void Catalogue::ajouterUv (const UV& uv) {
  if (this->existe(uv.tag())) {
    throw std::invalid_argument("L'uv existe déjà");
  } 

  this->_uvs[uv.tag()] = uv;
}

void Catalogue::supprimerUv (const QString& tag) {
  this->_uvs.remove(tag);
}

void Catalogue::editerUv (const QString& oldTag, const UV& uv) {
  if (uv.tag() != oldTag) {
    if (this->existe(uv.tag())) {
      throw std::invalid_argument("L'uv existe déjà");
    }

    this->_uvs.remove(oldTag);
  } 

  this->_uvs[uv.tag()] = uv; 
}

bool Catalogue::existe(QString& tag) {
  return this->_uvs.contains(tag);
}

QDomElement Catalogue::toXml () const {
  QDomDocument doc;
  QDomElement catalogue = doc.createElement(Catalogue::XML_NODE_NAME);
  
  for (int i = 0; i < this->_uvs().count(); i++) {
    catalogue.appendChild(this->_uvs()[i].toXml());
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
