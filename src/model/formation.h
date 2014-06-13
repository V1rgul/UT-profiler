#ifndef __FORMATION__
#define __FORMATION__

#include <QtXml>
#include <QList>

#include "semestre.h"
#include "xmlConvertible.h"

class Formation : public XmlConvertible {
  public:
    Formation () { _id = idCpt++; }

    inline unsigned int id () const { return _id; }
    inline unsigned int credits () const { return _credits; }
    inline QString nom () const { return _nom; }

    inline void nom (const QString& n) { _nom = n; }

    virtual void fromXml (const QDomNode& noeud) = 0;
    virtual QDomElement toXml () const = 0;

  private:
    static int idCpt;
    int _id;
    QString _nom;
    unsigned int _credits;
};

#endif
