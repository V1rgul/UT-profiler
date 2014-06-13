#ifndef __SEMESTRE__
#define __SEMESTRE__

#include <QtXml>
#include <QMap>
#include <QList>

#include "uvEtudiant.h"
#include "xmlConvertible.h"


class Semestre : public XmlConvertible {
  public:
    Semestre () { _id = idCpt++; }

    const static QString XML_NODE_NAME;
    void ajouterUv (const UVEtudiant* uv);
    void supprimerUv (const QString& tag);

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;
    inline QMap<QString, UVEtudiant> uvs () const { return _uvs; }
    inline int id () const { return _id; }
    inline QString nom () const { return _nom; }

    inline void nom (const QString& n) { _nom = n; }

  private:
    static int idCpt;
    int _id;
    QString _nom;
    bool dejaChoisie(const QString &tag) const;
    QMap<QString, UVEtudiant> _uvs;
};

#endif
