#include <stdexcept>

#include "catalogue.h"
#include "uv.h"

const QString Catalogue::XML_NODE_NAME = "catalogue";
const Catalogue* Catalogue::_instance = 0;

const Catalogue * Catalogue::instance () {
  if (!_instance) {
    _instance = Catalogue::charger();
  }

  return _instance;
}

UV* Catalogue::operator[] (QString tag) {
  return this->uvs()[tag];
}

const UV* Catalogue::operator[] (QString tag) const {
  return this->uvs()[tag];
}

void Catalogue::ajouterUv (UV* uv) {
  if (this->existe(uv->tag())) {
    throw std::invalid_argument("L'uv existe déjà");
  } 

  this->_uvs[uv->tag()] = uv;
}

void Catalogue::supprimerUv (const QString tag) {
  this->_uvs.remove(tag);
}

void Catalogue::editerUv (const QString oldTag, UV* uv) {
  if (uv->tag() != oldTag) {
    if (this->existe(uv->tag())) {
      throw std::invalid_argument("L'uv existe déjà");
    }

    this->_uvs.remove(oldTag);
  } 

  this->_uvs[uv->tag()] = uv; 
}

bool Catalogue::existe(QString tag) {
  return this->_uvs.contains(tag);
}

QDomElement Catalogue::toXml () const {
  QDomDocument doc;
  QDomElement catalogue = doc.createElement(Catalogue::XML_NODE_NAME);
  
  QMap<QString, UV*> uvs = this->uvs();
  QList<QString> keys = uvs.keys();

  for (int i = 0; i < keys.count(); i++) {
    catalogue.appendChild(uvs[keys[i]]->toXml());
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
    this->ajouterUv(uv);
  }
}

Catalogue* Catalogue::charger () {
  QFile f1(":/ressources/catalogue.xml");
  QFile f2("./catalogue.xml");
  QFile *f;

  QDomDocument dom = QDomDocument("doc");
  QString err;

  f = f2.exists() ? &f2 : &f1;

  if(!f->open(QIODevice::ReadOnly)) {
    throw f->errorString();
  }
  if (!dom.setContent(f, &err)) {
    f->close();
    throw err;
  }

  QDomElement domElement = dom.documentElement();
  Catalogue *c = new Catalogue();
  c->fromXml(domElement);

  f->close();
  return c;
}

void Catalogue::sauvegarder () {
  QDomDocument doc;
  QFile f("./catalogue.xml");
  QString err;

  if(!f.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
    throw f.errorString();
  }

  doc.appendChild(doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'")); 
  doc.appendChild(this->toXml());

  QTextStream out(&f);
  out << doc.toString();

  f.close(); 
}

QString Catalogue::toString () {
  QString ret = "Catalogue: \n";
  QMap<QString, UV*> uvs = this->uvs();
  QList<QString> keys = uvs.keys();

  for (int i = 0; i < keys.count(); i++) {
    ret += "*******************************\n";
    ret += uvs[keys[i]]->toString();
  }
  ret += "*******************************\n";

  return ret;
}
