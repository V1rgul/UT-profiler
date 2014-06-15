#ifndef __FORMATION_UTC__
#define __FORMATION_UTC__

#include <QtXml>
#include <QList>

#include "formation.h"
#include "semestre.h"
#include "xmlConvertible.h"

class FormationUtc : public Formation {
  public:
    FormationUtc () {}
    virtual ~FormationUtc() {}

    const static QString XML_NODE_NAME;

    void ajouterSemestre (Semestre* s);
    void supprimerSemestre (int id);

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QList<Semestre*> semestres () const { return _semestres; }
    inline unsigned int id () const { return _id; }
    inline QString nom () const { return _nom; }

    inline void nom (const QString& n) { _nom = n; }
    bool uvDejaValidee (const QString& tag, UVEtudiant* uv = 0) const;

  private:
    static int idCpt;
    bool verifierSemestre (const Semestre &s, QList<UVEtudiant>* dejaValidees = 0) const;
    int _id;
    QString _nom;
    QList<Semestre*> _semestres;
};

#endif
