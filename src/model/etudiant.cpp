#include <iostream>
#include <QtXml>
#include <QFile>

#include "catalogue.h"
#include "formation.h"
#include "formationUtc.h"
#include "formationHorsUtc.h"
#include "etudiant.h"

/**
 * @brief Nom du noeud XML correspondant à un étudiant
 */
const QString Etudiant::XML_NODE_NAME = "etudiant";

/**
 * @brief Nom du noeud XML correspondant aux préférences d'uvs d'un étudiant
 */
const QString Etudiant::PREFERENCE_XML_NODE_NAME = "preference";

/**
 * @brief Note de préférence par défaut
 */
const unsigned int Etudiant::NOTE_DEFAUT = 2;

/**
 * @brief Note de préférence maximum
 */
const unsigned int Etudiant::NOTE_MAX = 5;

/**
 * @brief Crée un étudiant
 */
Etudiant::Etudiant () {
  this->_formationUtc = new FormationUtc();
}

Etudiant::~Etudiant () {
  // supprimer formations
}

/**
 * @return Le chemin du fichier contenant les information de l'étudiant
 */
QString Etudiant::nomFichier () const {
  return "./etudiant/" + this->nom() + "_" + this->prenom() + ".xml";
}

/**
 * @brief Ajoute une formation hors utc
 * @param f La formation à ajouter
 */
void Etudiant::ajouterFormation (FormationHorsUtc* f) {
  this->_formationsHorsUtc.append(f);
}

/**
 * @brief Supprime une formation hors utc
 * @param id L'identifiant de la formation à supprimer
 */
void Etudiant::supprimerFormation (int id) {
  for (int i = 0; i < this->_formationsHorsUtc.count(); i++) {
    if (this->_formationsHorsUtc[i]->id() == id) {
      this->_formationsHorsUtc.removeAt(i);
      return;
    }
  }
}

/**
 * @param uv L'uv dont la note de préférence doit être retournée
 * @return La note de préférence pour l'uv, ou la note de préférence
 *    par défaut si l'étudiant n'a pas spécifié de note pour l'uv
 */
unsigned int Etudiant::preference (const UV* uv) const {
  return this->preferences()[uv];
}

/**
 * @param uv L'uv dont la note de préférence doit être définie
 * @param note La note de préférence pour l'uv
 */
void Etudiant::preference (const UV* uv, unsigned int note) {
  if (note > Etudiant::NOTE_MAX) {
    throw std::invalid_argument("Note invalide");
  }
  this->_preferences[uv] = note;
}

/**
 * @param saison La saison à laquelle les UVs doivent être enseignées
 * @param cursus La liste des cursus à afficher, si cursus vaut NULL,
 *    les UVs de tous les cursus pour la saison donnée sont retournées
 *
 * @return Les préférences de l'étudiant pour les UVs
 *    enseignés durant la saison passé en argument et appartenant aux
 *    cursus donnés
 */
QMap<const UV*, unsigned int> Etudiant::preferences (
    Semestre::Saison saison, QStringList* cursus) const 
{
  QList<const UV*> uvs = this->preferences().keys();
  QMap<const UV*, unsigned int> triees;
  for (int j = 0; j < uvs.count(); j++) {
    bool matchSaison = 
      (saison == Semestre::AUTOMNE && uvs[j]->automne()) ||
      (saison == Semestre::PRINTEMPS && uvs[j]->printemps());
    bool dejaValidee = this->formationUtc()->uvDejaValidee(uvs[j]->tag());
    bool matchCursus = false;
    if (!cursus) { matchCursus = true; }
    else {
      for (int k = 0; k < cursus->count(); k++) {
        if (uvs[j]->cursus().contains((*cursus)[k])) {
          matchCursus = true;
          break;
        }
      }
    }
    if (matchSaison && !dejaValidee && matchCursus) { 
      triees[uvs[j]] = this->preference(uvs[j]); 
    }
  }
 
  return triees;
}

/**
 * @return Les crédits de l'étudiant dans les diverses catégorie d'UVs,
 *    la clef "total" contient la somme de tous les crédits de l'étudiant,
 *    et la clef "BR" contient la somme des crédits de type CS et TM
 */
QMap<QString, unsigned int> Etudiant::credits () const {
  QMap<QString, unsigned int> credits;

  for (int i = 0; i < this->_formationsHorsUtc.count(); i++) {
    credits["CS"] += this->_formationsHorsUtc[i]->creditsCS();  
    credits["TM"] += this->_formationsHorsUtc[i]->creditsTM();  
    credits["TSH"] += this->_formationsHorsUtc[i]->creditsTSH();  
  }

  credits["total"] = credits["CS"] + credits["TM"] + credits["TSH"];

  QList<Semestre*> semestres = _formationUtc->semestres();
  for (int i = 0; i < semestres.count(); i++) {
    Semestre* s = semestres[i];
    QMap<QString, UVEtudiant*> uvs = s->uvs();

    for (int j = 0; j < uvs.keys().count(); j++) {
      UVEtudiant* u = uvs[uvs.keys()[j]];
      for (int k = 0; k < u->credits().keys().count(); k++) {
        QString type = u->credits().keys()[k];
        unsigned int c = u->credits()[type];

        if (credits.contains(type)) { credits[type] += c; }
        else { credits[type] = c;} 

        credits["total"] += c;
      } 
    }   
  } 

  // L'utc demande 30 crédits CS, 30 crédits TM, la somme
  // des crédits CS/TM doit être au dessus de 80 (crédits BR)
  // pour le cycle ingénieur
  credits["BR"] = credits["CS"] + credits["TM"];

  return credits;
}

/**
 * @return La liste des crédits necessaires par catégorie d'UV
 */
QMap<QString, unsigned int> Etudiant::creditsNecessaires () {
  QMap<QString, unsigned int> credits;

  QFile f(":/ressources/credits.xml");
  QDomDocument dom = QDomDocument("doc");
  QString err;

  if(!f.open(QIODevice::ReadOnly)) {
    throw f.errorString();
  }
  if (!dom.setContent(&f, &err)) {
    f.close();
    throw "erreur lors de l'association fichier/Dom";
  }

  QDomElement domElement = dom.documentElement();

  QDomNodeList child = domElement.childNodes();
  for (int i = 0; i < child.count(); i++) {
    QDomNode c = child.at(i);
    QDomElement e = c.toElement();
    QString type = e.attribute("type");
    credits[type] = e.text().toInt();
  }

  f.close();
  return credits;
}

QDomElement Etudiant::toXml () const {
  QDomDocument doc;
  QDomElement etudiant = doc.createElement(Etudiant::XML_NODE_NAME);
  etudiant.setAttribute("nom", this->nom());
  etudiant.setAttribute("prenom", this->prenom());

  etudiant.appendChild(this->formationUtc()->toXml());

  for (int i = 0; i < this->formationsHorsUtc().count(); i++) {
    etudiant.appendChild(this->formationsHorsUtc()[i]->toXml());
  }

  for (int i = 0; i < this->preferences().keys().count(); i++) {
    const UV* uv = this->preferences().keys()[i];
    unsigned int note = this->preferences()[uv];

    if (note != Etudiant::NOTE_DEFAUT) {
      QDomElement e = doc.createElement(Etudiant::PREFERENCE_XML_NODE_NAME);
      e.setAttribute("uv", uv->tag());
      e.setAttribute("note", note);
      etudiant.appendChild(e);
    }
  }

  return etudiant;
}

void Etudiant::fromXml (const QDomNode& noeud) {
  if (noeud.nodeName() != Etudiant::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
  this->prenom(e.attribute("prenom"));

  QDomNodeList child = noeud.childNodes();
  const Catalogue* c = Catalogue::instance();

  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() == FormationUtc::XML_NODE_NAME) {
      this->formationUtc()->fromXml(child.at(i));
    }
    else if (child.at(i).nodeName() == FormationHorsUtc::XML_NODE_NAME) {
      FormationHorsUtc *f = new FormationHorsUtc();
      f->fromXml(child.at(i));
      this->ajouterFormation(f);
    }
    else if (child.at(i).nodeName() == Etudiant::PREFERENCE_XML_NODE_NAME) {
      QDomElement ce = child.at(i).toElement();
      const UV* uv = (*c)[ce.attribute("uv")];
      unsigned int note = ce.attribute("note").toInt();
      this->_preferences[uv] = note;
    }
    else {
      throw QString("Les noeuds etudiant ne peuvent contenir que des noeuds formation");
    }
  }

  QList<UV*> uvs = c->uvs().values();
  for (int i = 0; i < uvs.count(); i++) {
    UV* u = uvs[i];
    if (!this->_preferences.contains(u)) {
      this->_preferences[u] = Etudiant::NOTE_DEFAUT;
    }
  }

}

Etudiant* Etudiant::charger (const QString& nomComplet) {
  QStringList s = nomComplet.split(' ');
  return Etudiant::charger (s.at(0), s.at(1));
}

Etudiant* Etudiant::charger (const QString& nom, const QString& prenom) {
  Etudiant *e = new Etudiant();
  e->nom(nom);
  e->prenom(prenom);

  QFile f(e->nomFichier());
  QDomDocument dom = QDomDocument("doc");
  QString err;

  if(!f.open(QIODevice::ReadOnly)) {
    throw "Etudiant::charger: Impossible d'ouvrir le fichier";
  }
  if (!dom.setContent(&f, &err)) {
    f.close();
    throw "Etudiant::charger: " + err;
  }

  QDomElement domElement = dom.documentElement();
  e->fromXml(domElement);

  f.close();
  return e;
}

void Etudiant::sauvegarder () {
  if (this->nom().isEmpty() || this->prenom().isEmpty()) {
    throw QString("L'étudiant ne peut être sauvegardé sans nom et prénom");
  }

  QDir dir("./etudiant");
  if (!dir.exists()) {
    QDir().mkdir("./etudiant");
  }
  QDomDocument doc;
  QFile f(this->nomFichier());
  QString err;

  if(!(f.open(QIODevice::ReadWrite | QIODevice::Truncate))) {
    throw f.errorString();
  }

  doc.appendChild(doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'")); 
  doc.appendChild(this->toXml());

  QTextStream out(&f);
  out << doc.toString();

  f.close(); 
}

QStringList Etudiant::listeEtudiants () {
  QStringList fichiers = QDir("./etudiant").entryList(QDir::Files | QDir::NoDotAndDotDot);
  for (int i = 0; i < fichiers.count(); i++) {
    fichiers[i] = fichiers[i].replace('_', ' ');
    fichiers[i].resize(fichiers[i].length() - 4);
  }

  return fichiers;
}
