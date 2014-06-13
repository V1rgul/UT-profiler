#ifndef __SEMESTRE__
#define __SEMESTRE__

#include <QtXml>
#include <QMap>
#include <QList>

#include "uvEtudiant.h"
#include "xmlConvertible.h"


class Equivalence : public XmlConvertible {
  public:
    Equivalence () { _id = idCpt++; }

    const static QString XML_NODE_NAME;

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;
    inline int id () const { return _id; }
    inline QString nom () const { return _nom; }
    inline QMap<QString, unsigned int> credits () const { return _credits; }

    inline void nom (const QString& n) { _nom = n; }

  private:
    static int idCpt;
    int _id;
    QString _nom;
    QMap<QString, unsigned int> _credits;
};

#endif
