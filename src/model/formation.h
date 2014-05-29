#ifndef __FORMATION__
#define __FORMATION__

#include <QtXml>
#include <QList>

#include "semestre.h"
#include "xmlConvertible.h"

class Formation : public XmlConvertible {
  public:
    const static QString XML_NODE_NAME;
    void ajouterSemestre (Semestre s);
    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;
    QString xmlNodeName () const;
    inline QList<Semestre> semestres () const { return _semestres; }

  private:
    QList<Semestre> _semestres;
};

#endif
