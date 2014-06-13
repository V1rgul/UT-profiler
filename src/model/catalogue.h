#ifndef __CATALOGUE__
#define __CATALOGUE__

#include <QString>
#include <QMap>
#include "uv.h"
#include "xmlConvertible.h"

class Catalogue : public XmlConvertible {
  public:
    static const QString XML_NODE_NAME;

    static const Catalogue* instance ();

    UV* operator[] (QString tag);
    const UV* operator[] (QString tag) const;

    void ajouterUv (UV* uv);
    void supprimerUv (const QString uv);
    void editerUv (const QString oldTag, UV* uv);
    bool existe (QString tag);

    void sauvegarder ();

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QMap<QString, UV*> uvs () const { return _uvs; }

    QString toString ();
  private:
    Catalogue () {} 
    static const Catalogue* _instance;
    static Catalogue* charger ();
    QMap<QString, UV*> _uvs;
};

#endif
