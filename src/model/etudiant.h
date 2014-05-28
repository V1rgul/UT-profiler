#ifndef __ETUDIANT__
#define __ETUDIANT__

#include "formation.h"

#include <QList>
#include <QString>
#include <QFile>

class Etudiant {
  public:
    inline QList<Formation> formations () const { return _formations; }

    inline QString nom () const { return _nom; }
    inline void nom (const QString n) { _nom = n; }
    inline QString prenom () const { return _prenom; }
    inline void prenom (const QString p) { _prenom = p; }

    void sauvegarder ();

  private:
    QList<Formation> _formations;
    QString _nom, _prenom;

    QString* nomFichier ();
    QFile* fichier (QIODevice::OpenMode mode);
};

#endif
