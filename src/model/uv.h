#ifndef __UV__
#define __UV__

#include <QString>
#include <QList>

enum Cursus {TC, GI, GB, GP, GSU, GM, GSM, HUTECH, TSH}

class UV : public XmlConvertible {
  public:
    static const UV::XML_NODE_NAME;

    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QString tag () const { return _tag; }
    inline QString titre () const { return _titre; }
    inline QStringList cursus () const { return _cursus; }
    inline bool automne () const { return _automne; }
    inline bool printemps () const { return _printemps; }
    inline unsigned int credits () const { return _credits; }

    inline void tag (const QString& t) { _tag = t; }
    inline void titre (const QString& d) { _titre = d; }
    inline void automne (bool a) { _automne = a; }
    inline void printemps (bool p) { _printemps = p; }
    inline void credits (unsigned int c) { _credits = c; }
  private:
    QString _tag, _titre;
    QStringList _cursus;
    bool _automne, _printemps;
    unsigned int _credits;
};

#endif
