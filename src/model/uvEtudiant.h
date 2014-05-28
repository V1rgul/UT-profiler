#ifndef __UV_ETUDIANT__
#define __UV_ETUDIANT__

#include <QString>

class UVEtudiant {
  public:
    enum Note {EN_COURS, RES, ABS, FX, F, E, D, C, B, A};

    inline QString tag () const { return _tag; }
    inline void tag (const QString t) { _tag = t; }

    inline enum Note note () const { return _note; }
    inline void note (enum Note n) { _note = n; }

  private:
    QString _tag;
    enum Note _note;
};

#endif
