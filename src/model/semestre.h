#ifndef __SEMESTRE__
#define __SEMESTRE__

#include <QtXml>
#include <QList>

#include "uvEtudiant.h"
#include "xmlConvertible.h"


class Semestre : public XmlConvertible {
  public:
    const static QString XML_NODE_NAME;
    void ajouterUv (UVEtudiant uv);

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;
    inline QList<UVEtudiant> uvs () const { return _uvs; }

  private:
    QList<UVEtudiant> _uvs;
};

#endif
