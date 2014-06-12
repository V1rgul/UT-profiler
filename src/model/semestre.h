#ifndef __SEMESTRE__
#define __SEMESTRE__

#include <QtXml>
#include <QMap>
#include <QList>

#include "uvEtudiant.h"
#include "xmlConvertible.h"


class Semestre : public XmlConvertible {
  public:
    const static QString XML_NODE_NAME;
    void ajouterUv (const UVEtudiant* uv);

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;
    inline QMap<QString, UVEtudiant> uvs () const { return _uvs; }

  private:
    bool dejaChoisie(const QString &tag) const;
    QMap<QString, UVEtudiant> _uvs;
};

#endif
