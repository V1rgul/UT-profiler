#include <iostream>
#include <QtXml>
#include <QFile>

#include "formation.h"
#include "formationUtc.h"
#include "formationHorsUtc.h"
#include "etudiant.h"

const QString Etudiant::XML_NODE_NAME = "etudiant";

Etudiant::Etudiant () {
  this->_formationUtc = new FormationUtc();
}

Etudiant::~Etudiant () {
  // supprimer formations
}

QString Etudiant::nomFichier () const {
  return "./etudiant/" + this->nom() + "_" + this->prenom() + ".xml";
}

void Etudiant::ajouterFormation (FormationHorsUtc* f) {
  this->_formationsHorsUtc.append(f);
}

void Etudiant::supprimerFormation (int id) {
  for (int i = 0; i < this->_formationsHorsUtc.count(); i++) {
    if (this->_formationsHorsUtc[i]->id() == id) {
      this->_formationsHorsUtc.removeAt(i);
      return;
    }
  }
}

QMap<QString, unsigned int> Etudiant::credits () const {
  QMap<QString, unsigned int> credits;
  credits["horsUtc"] = 0;

  for (int i = 0; i < this->_formationsHorsUtc.count(); i++) {
    credits["horsUtc"] += this->_formationsHorsUtc[i]->credits();  
  }

  credits["total"] = credits["horsUtc"];

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

        // L'utc demande 30 crédits CS, 30 crédits TM, la somme
        // des crédits CS/TM doit être au dessus de 80 (crédits BR)
        // pour le cycle ingénieur
        if (type == "CS" || type == "TM") {
          if (credits.contains("BR")) { credits["BR"] += c; }
          else { credits["BR"] = c; } 
        }

        credits["total"] += c;
      } 
    }   
  } 

  return credits;
}

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

  return etudiant;
}

void Etudiant::fromXml (QDomNode& noeud) {
  if (noeud.nodeName() != Etudiant::XML_NODE_NAME) {
    throw "Fichier XML invalide";
  }

  QDomElement e = noeud.toElement();
  this->nom(e.attribute("nom"));
  this->prenom(e.attribute("prenom"));

  QDomNodeList child = noeud.childNodes();
  for (int i = 0; i < child.count(); i++) {
    if (child.at(i).nodeName() == FormationUtc::XML_NODE_NAME) {
      this->formationUtc()->fromXml(child.at(i));
    }
    else if (child.at(i).nodeName() == FormationHorsUtc::XML_NODE_NAME) {
      FormationHorsUtc *f = new FormationHorsUtc();
      f->fromXml(child.at(i));
      this->ajouterFormation(f);
    }
    else {
      throw QString("Les noeuds etudiant ne peuvent contenir que des noeuds formation");
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
