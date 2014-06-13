#ifndef __FORMATION_HORS_UTC__
#define __FORMATION_HORS_UTC__

#include <QtXml>
#include <QList>

#include "xmlConvertible.h"

class FormationHorsUtc : public Formation {
  public:
    const static QString XML_NODE_NAME;

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline unsigned int credits () const { return _credits; }
    inline QString nom () const { return _nom; }

    inline void nom (const QString& n) { _nom = n; }

    inline bool utc () { return false; }

  private:
    QString _nom;
    unsigned int _credits;
};

#endif
