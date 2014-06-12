#ifndef __FORMATION__
#define __FORMATION__

#include <QtXml>
#include <QList>

#include "semestre.h"
#include "xmlConvertible.h"

class Formation : public XmlConvertible {
  public:
    const static QString XML_NODE_NAME;
    void ajouterSemestre (const Semestre* s);
    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;
    QString xmlNodeName () const;
    inline QList<Semestre> semestres () const { return _semestres; }
    inline unsigned int credits () const { return _credits; }
    inline void credits (unsigned int c) { _credits = c; }

  private:
    bool verifierSemestre (const Semestre &s, QList<UVEtudiant>* dejaValidees = 0) const;
    bool uvDejaValidee (const QString& tag, UVEtudiant* uv = 0) const;
    QList<Semestre> _semestres;
    unsigned int _credits;
};

#endif
