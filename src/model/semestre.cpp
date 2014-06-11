#include <stdexcept>
#include <QList>
#include <QtXml>

#include "semestre.h"

const QString Semestre::XML_NODE_NAME = "semestre";

void Semestre::ajouterUv (const UVEtudiant* uv) {
  if (this->dejaChoisie(uv->tag())) {
    throw std::invalid_argument("Uv déjà choisie !");
  }
  this->_uvs[uv->tag()] = *uv;
}

bool Semestre::dejaChoisie(const QString &tag) const {
  return this->uvs().contains(tag);
}

void Semestre::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != Semestre::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != UVEtudiant::XML_NODE_NAME) {
      throw "Les noeuds semestre ne peuvent contenir que des noeuds uv";
    }
    UVEtudiant *uv = new UVEtudiant();
    uv->fromXml(child.at(i));
    this->ajouterUv(uv);
  }
}

QDomElement Semestre::toXml () const {
  QDomDocument doc;
  QDomElement semestre = doc.createElement(Semestre::XML_NODE_NAME);

  QList<QString> tags = this->uvs().keys();
  for (int i = 0; i < tags.count(); i++) { 
    semestre.appendChild(this->uvs().value(tags[i]).toXml());
  }

  return semestre;
}
