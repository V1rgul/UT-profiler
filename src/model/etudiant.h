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

class Etudiant : public XmlConvertible {
  public:
    Etudiant ();
    ~Etudiant ();

    const static QString XML_NODE_NAME;
    const static QString PREFERENCE_XML_NODE_NAME;
    const static unsigned int NOTE_DEFAUT;
    const static unsigned int NOTE_MAX;

    static Etudiant* charger (const QString& nom, const QString& prenom);
    static Etudiant* charger (const QString& nomComplet);
    static QStringList listeEtudiants ();

    void sauvegarder ();
    void ajouterFormation (FormationHorsUtc* f);
    void supprimerFormation (int id);

    inline QMap<const UV*, unsigned int> preferences () const {
      return _preferences;
    }
    QMap<const UV*, unsigned int> preferences (
        Semestre::Saison saison, QStringList* cursus = 0) const;

    unsigned int preference (const UV* uv) const;
    void preference (const UV* uv, unsigned int note);

    QMap<QString, unsigned int> credits () const;
    static QMap<QString, unsigned int> creditsNecessaires ();

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline FormationUtc* formationUtc () const { return _formationUtc; }
    inline QList<FormationHorsUtc*> formationsHorsUtc () const { return _formationsHorsUtc; }
    inline QString nom () const { return _nom; }
    inline void nom (const QString& n) { _nom = n; }
    inline QString prenom () const { return _prenom; }
    inline void prenom (const QString& p) { _prenom = p; }

  private:
    bool uvCompare (const UV* uv1, const UV* uv2);
    FormationUtc* _formationUtc;
    QList<FormationHorsUtc*> _formationsHorsUtc;
    QMap<const UV*, unsigned int> _preferences;
    QString _nom; 
    QString _prenom;

    QString nomFichier () const;
};

#endif
