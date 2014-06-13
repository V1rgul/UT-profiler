#ifndef __UV__
#define __UV__

#include <QString>
#include <QStringList>
#include <QtXml>
#include "xmlConvertible.h"

class UV : public XmlConvertible {
  public:
    static const QString XML_NODE_NAME;
    static const QString CREDIT_XML_NODE_NAME;

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QString tag () const { return _tag; }
    inline QString titre () const { return _titre; }
    inline QStringList cursus () const { return _cursus; }
    inline bool automne () const { return _automne; }
    inline bool printemps () const { return _printemps; }
    inline QMap<QString, unsigned int> credits () const { return _credits; }

    inline void tag (const QString& t) { _tag = t; }
    inline void titre (const QString& d) { _titre = d; }
    inline void cursus (const QStringList& c) { _cursus = c; }
    inline void automne (bool a) { _automne = a; }
    inline void printemps (bool p) { _printemps = p; }

    QString toString ();
  private:
    QString _tag, _titre;
    QStringList _cursus;
    bool _automne, _printemps;
    QMap<QString, unsigned int> _credits;
};

#endif
