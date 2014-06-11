#include <QMap>
#include <QtXml>
#include "semestreInvalideErreur.h"
#include "formation.h"

const QString Formation::XML_NODE_NAME = "formation";

void Formation::ajouterSemestre (const Semestre* s) {
  QList<UVEtudiant> dejaValidees;
  if (!this->verifierSemestre(*s, &dejaValidees)) {
    throw semestreInvalideErreur(dejaValidees);
  }
  this->_semestres.append(*s);
}

bool Formation::verifierSemestre (const Semestre &s, QList<UVEtudiant>* dejaValidees) const {
  QList<UVEtudiant> uvs = s.uvs().values();
  UVEtudiant ret;

  for (int i = 0; i < uvs.count(); i++) {
    if (uvDejaValidee(uvs[i].tag(), &ret)) {
      if (dejaValidees) {
        dejaValidees->append(ret);
      }  
      else {
        return false;
      }
    }
  }

  if (dejaValidees) { return dejaValidees->count() == 0; }
  return true;
}

bool Formation::uvDejaValidee(const QString& tag, UVEtudiant* uv) const {
  QList<Semestre> s = this->semestres();
  for (int i = 0; i < s.count(); i++) {
    if (s[i].uvs().contains(tag)) {
      *uv = s[i].uvs().value(tag);
      return true;
    }
  }

  return false;
}

void Formation::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != Formation::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != Semestre::XML_NODE_NAME) {
      throw "Les noeuds formation ne peuvent contenir que des noeuds semestre";
    }
    Semestre *s = new Semestre();
    s->fromXml(child.at(i));
    this->ajouterSemestre(s);
  }
}

QDomElement Formation::toXml () const {
  QDomDocument doc;
  QDomElement formation = doc.createElement(Formation::XML_NODE_NAME);

  for (int i = 0; i < this->semestres().count(); i++) {
    formation.appendChild(this->semestres()[i].toXml());
  }

  return formation;
}

