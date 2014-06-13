#ifndef __ETUDIANT__
#define __ETUDIANT__

#include <QList>
#include <QString>
#include <QFile>
#include <QtXml>

#include "formation.h"
#include "formationUtc.h"
#include "formationHorsUtc.h"
#include "xmlConvertible.h"

// BUG: Si la classe hérite de XmlConvertible, et donc que la méthode
// toXml surcharge la méthode virtuelle pure de la classe XmlConvertible,
// le programme crash dans la fonction sauvegarder a la ligne
// doc.appendChild(this->toXml()). Le mot clef this dois poser probleme
// mais je sais pas comment le corriger
class Etudiant {
  public:
    Etudiant ();
    virtual ~Etudiant ();

    const static QString XML_NODE_NAME;
    static Etudiant* charger (const QString& nom, const QString& prenom);
    static Etudiant* charger (const QString& nomComplet);
    static QStringList listeEtudiants ();

    void sauvegarder ();
    void ajouterFormation (FormationHorsUtc* f);
    void supprimerFormation (int id);

    void fromXml (QDomNode& noeud);
    QDomElement toXml () const;
    QString xmlNodeName () const;

    inline FormationUtc* formationUtc () const { return _formationUtc; }
    inline QList<FormationHorsUtc*> formationsHorsUtc () const { return _formationsHorsUtc; }
    inline QString nom () const { return _nom; }
    inline void nom (const QString& n) { _nom = n; }
    inline QString prenom () const { return _prenom; }
    inline void prenom (const QString& p) { _prenom = p; }

  private:
    FormationUtc* _formationUtc;
    QList<FormationHorsUtc*> _formationsHorsUtc;
    QString _nom; 
    QString _prenom;

    QString nomFichier () const;
};

#endif
