#include <stdexcept>

#include "catalogue.h"
#include "uv.h"

/**
 * @brief Nom du noeud XML correspondant au catalogue
 */
const QString Catalogue::XML_NODE_NAME = "catalogue";

const Catalogue* Catalogue::_instance = 0;

/**
 * @return Le singleton du catalogue
 */
const Catalogue * Catalogue::instance () {
  if (!_instance) {
    _instance = Catalogue::charger();
  }

  return _instance;
}

/**
 * @param tag Le tag de l'uv
 * @return L'uv ayant le tag passé en argument
 */
UV* Catalogue::operator[] (QString tag) {
  return this->uvs()[tag];
}

/**
 * @param tag Le tag de l'uv
 * @return L'uv ayant le tag passé en argument
 */
const UV* Catalogue::operator[] (QString tag) const {
  return this->uvs()[tag];
}

/**
 * @brief Ajoute une uv au catalogue
 * @param uv L'uv à ajouter
 */
void Catalogue::ajouterUv (UV* uv) {
  if (this->existe(uv->tag())) {
    throw std::invalid_argument("L'uv existe déjà");
  } 

  this->_uvs[uv->tag()] = uv;
}

/**
 * @brief Supprime une uv du catalogue
 * @param tag Le tag de l'uv à supprimer
 */
void Catalogue::supprimerUv (const QString tag) {
  this->_uvs.remove(tag);
}

/**
 * @brief Edite une uv du catalogue
 * @param oldTag L'ancien nom de l'uv
 * @param uv L'uv éditée
 */
void Catalogue::editerUv (const QString oldTag, UV* uv) {
  if (uv->tag() != oldTag) {
    if (this->existe(uv->tag())) {
      throw std::invalid_argument("L'uv existe déjà");
    }

    this->_uvs.remove(oldTag);
  } 

  this->_uvs[uv->tag()] = uv; 
}

/**
 * @param tag Le tag de l'uv
 * @return Vrai si le catalogue contient l'uv, faux sinon
 */
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

    // Ajout des cursus à la liste des cursus
    for (int j = 0; j < uv->cursus().count(); j++) {
      if (uv->cursus()[j] != "") {
        this->_cursus.insert(uv->cursus()[j]); 
      }
    }

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
