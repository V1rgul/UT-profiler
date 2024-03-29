#include <stdexcept>
#include <QList>
#include <QtXml>
#include <QDate>

#include "semestre.h"

/**
 * @brief Nom du noeud XML correspondant à un semestre 
 */
const QString Semestre::XML_NODE_NAME = "semestre";
int Semestre::idCpt = 0;

/**
 * @brief Ajoute une uv au semestre
 * @param uv L'uv à ajouter
 */
void Semestre::ajouterUv (UVEtudiant* uv) {
  if (this->dejaChoisie(uv->tag())) {
    throw std::invalid_argument("Uv déjà choisie !");
  }
  this->_uvs[uv->tag()] = uv;
}

/**
 * @brief Supprime une uv du semestre
 * @param tag Le tag de l'uv à supprimer
 */
void Semestre::supprimerUv (const QString& tag) {
  this->_uvs.remove(tag);
}

bool Semestre::dejaChoisie(const QString &tag) const {
  return this->uvs().contains(tag);
}

void Semestre::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != Semestre::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  QDate date;
  int anneeCourante = date.year();

  this->nom(e.attribute("nom"));
  if (e.hasAttribute("annee")) { this->annee(e.attribute("annee").toInt()); }
  else { this->annee(anneeCourante); }

  this->saison(e.attribute("saison") == "printemps" ?
      Semestre::PRINTEMPS :
      Semestre::AUTOMNE);
  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() != UVEtudiant::XML_NODE_NAME) {
      throw "Les noeuds semestre ne peuvent contenir que des noeuds uv";
    }
    UVEtudiant *uv = new UVEtudiant(child.at(i));
    uv->fromXml(child.at(i));
    this->ajouterUv(uv);
  }
}

QDomElement Semestre::toXml () const {
  QDomDocument doc;
  QDomElement semestre = doc.createElement(Semestre::XML_NODE_NAME);
  
  semestre.setAttribute("nom", this->nom());
  semestre.setAttribute("annee", this->annee());
  semestre.setAttribute("saison", this->saison() == Semestre::PRINTEMPS ?
                                  "printemps" : "automne");
  QList<QString> tags = this->uvs().keys();
  for (int i = 0; i < tags.count(); i++) { 
    semestre.appendChild(this->uvs().value(tags[i])->toXml());
  }

  return semestre;
}
