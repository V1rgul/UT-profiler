#ifndef __UV_ETUDIANT__
#define __UV_ETUDIANT__

#include <stdexcept>
#include <QtXml>
#include <QSet>
#include <QString>

#include "uv.h"
#include "xmlConvertible.h"

class UVEtudiant : public XmlConvertible {
  public:
    const static QString XML_NODE_NAME;

    UVEtudiant (const UV& uv) : _details(&uv) {}
    UVEtudiant (const QDomNode& node) {
      this->fromXml(node); 
    }

    virtual ~UVEtudiant () {}
    void fromXml (const QDomNode& noeud);
    QDomElement toXml () const;

    inline QString tag () const { return _details->tag(); }
    inline QString titre () const { return _details->titre(); }
    inline QStringList cursus () const { return _details->cursus(); }
    inline bool automne () const { return _details->automne(); }
    inline bool printemps () const { return _details->printemps(); }
    inline QMap<QString, unsigned int> credits () const { return _details->credits(); }

    inline QString note () const { return _note; }
    inline void note (const QString& n) { 
      if (!n.isEmpty() && !listeNotes().contains(n)) {
        throw std::invalid_argument("Note invalide");
      } 
      _note = n; 
    }

  private:
    static QSet<QString> listeNotes ();
    QString _tag, _note;
    const UV* _details;
};

#endif
