#ifndef __CATALOGUE__
#define __CATALOGUE__

#include <QString>
#include <QMap>
#include "uv.h"
#include "xmlConvertible.h"

class Catalogue : public XmlConvertible {
  public:
    static const QString XML_NODE_NAME;

    void ajouterUv (const UV& uv);
    void supprimerUv (const QString uv);
    void editerUv (const QString oldTag, const UV& uv);
    bool existe (QString tag);

    static Catalogue* charger ();
    void sauvegarder ();

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QMap<QString, UV> uvs () const { return _uvs; }

    QString toString ();
  private:
    Catalogue () {} 
    QMap<QString, UV> _uvs;
};

#endif
