#include <QMap>
#include <QtXml>
#include "semestreInvalideErreur.h"
#include "formationUtc.h"

const QString FormationUtc::XML_NODE_NAME = "formation-utc";

void FormationUtc::ajouterSemestre (Semestre* s) {
  QList<UVEtudiant> dejaValidees;
  if (!this->verifierSemestre(*s, &dejaValidees)) {
    throw semestreInvalideErreur(dejaValidees);
  }
  this->_semestres.append(s);
}

void FormationUtc::supprimerSemestre (int id) {
  for (int i = 0; i < this->_semestres.count(); i++) {
    if (this->_semestres[i]->id() == id) {
      this->_semestres.removeAt(i);
      return;
    }
  }
}

bool FormationUtc::verifierSemestre (const Semestre &s, QList<UVEtudiant>* dejaValidees) const {
  QList<UVEtudiant*> uvs = s.uvs().values();
  UVEtudiant *ret = 0;

  for (int i = 0; i < uvs.count(); i++) {
    if (uvDejaValidee(uvs[i]->tag(), ret)) {
      if (dejaValidees) {
        dejaValidees->append(*ret);
      }  
      else {
        return false;
      }
    }
  }

  if (dejaValidees) { return dejaValidees->count() == 0; }
  return true;
}

bool FormationUtc::uvDejaValidee(const QString& tag, UVEtudiant* uv) const {
  QList<Semestre*> s = this->semestres();
  for (int i = 0; i < s.count(); i++) {
    if (s[i]->uvs().contains(tag)) {
      uv = s[i]->uvs().value(tag);
      return true;
    }
  }

  return false;
}

void FormationUtc::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != FormationUtc::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
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

QDomElement FormationUtc::toXml () const {
  QDomDocument doc;
  QDomElement formation = doc.createElement(FormationUtc::XML_NODE_NAME);

  formation.setAttribute("nom", this->nom());
  for (int i = 0; i < this->semestres().count(); i++) {
    formation.appendChild(this->semestres()[i]->toXml());
  }

  return formation;
}

