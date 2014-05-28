#ifndef __FORMATION__
#define __FORMATION__

#include "semestre.h"

#include <QList>

class Formation {
  private:
    QList<Semestre> _semestres;

  public:
    inline QList<Semestre> semestre () const { return _semestres; }
};

#endif
