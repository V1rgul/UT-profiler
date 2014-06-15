#ifndef __FORMATION_HORS_UTC__
#define __FORMATION_HORS_UTC__

#include <QtXml>
#include <QList>

#include "formation.h"
#include "xmlConvertible.h"

class FormationHorsUtc : public Formation {
  public:
    FormationHorsUtc () {}
    virtual ~FormationHorsUtc () {}

    const static QString XML_NODE_NAME;

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline unsigned int creditsCS () const { return _creditsCS; }
    inline unsigned int creditsTM () const { return _creditsTM; }
    inline unsigned int creditsTSH () const { return _creditsTSH; }

    inline QString nom () const { return _nom; }

    inline void nom (const QString& n) { _nom = n; }
    inline void creditsCS (unsigned int c) { _creditsCS = c; }
    inline void creditsTM (unsigned int c) { _creditsTM = c; }
    inline void creditsTSH (unsigned int c) { _creditsTSH = c; }

  private:
    QString _nom;
    unsigned int _creditsCS;
    unsigned int _creditsTM;
    unsigned int _creditsTSH;
};

#endif

