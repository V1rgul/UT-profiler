#ifndef __UV_ETUDIANT__
#define __UV_ETUDIANT__

#include <stdexcept>
#include <QtXml>
#include <QSet>
#include <QString>

#include "xmlConvertible.h"

class UVEtudiant : public XmlConvertible {
  public:
    const static QString XML_NODE_NAME;

    virtual ~UVEtudiant () {}
    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QString tag () const { return _tag; }
    inline void tag (const QString t) { _tag = t; }

    inline QString note () const { return _note; }
    inline void note (const QString& n) { 
      if (!listeNotes().contains(n)) {
        throw std::invalid_argument("Note invalide");
      } 
      _note = n; 
    }

  private:
    static QSet<QString> listeNotes ();
    QString _tag, _note;
};

#endif
