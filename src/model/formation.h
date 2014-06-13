#ifndef __FORMATION__
#define __FORMATION__

#include <QtXml>
#include <QList>

#include "semestre.h"
#include "xmlConvertible.h"

class Formation : public XmlConvertible {
  public:
    Formation () { _id = idCpt++; }

    const static QString XML_NODE_NAME;

    void ajouterSemestre (const Semestre* s);
    void supprimerSemestre (int id);

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QList<Semestre> semestres () const { return _semestres; }
    inline unsigned int id () const { return _id; }
    inline unsigned int credits () const { return _credits; }
    inline QString nom () const { return _nom; }

    inline void nom (const QString& n) { _nom = n; }

  private:
    static int idCpt;
    bool verifierSemestre (const Semestre &s, QList<UVEtudiant>* dejaValidees = 0) const;
    bool uvDejaValidee (const QString& tag, UVEtudiant* uv = 0) const;
    int _id;
    QString _nom;
    QList<Semestre> _semestres;
    unsigned int _credits;
};

#endif
