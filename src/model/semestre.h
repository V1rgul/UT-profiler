#ifndef __SEMESTRE__
#define __SEMESTRE__

#include "uvEtudiant.h"

#include <QList>

class Semestre {
  private:
    QList<UVEtudiant> _uvs;

  public:
    inline QList<UVEtudiant> uvs () const { return _uvs; }
};

#endif
