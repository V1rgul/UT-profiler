#ifndef __SEMESTRE_INVALIDE__
#define __SEMESTRE_INVALIDE__

#include <exception>
#include <QList>
#include "uvEtudiant.h"

class semestreInvalideErreur : public std::exception {
  public:
    semestreInvalideErreur (QList<UVEtudiant>& dejaValidees):_dejaValidees(dejaValidees) {
      for (int i = 0; i < dejaValidees.count(); i++) {
        _msg += dejaValidees[i].tag() + " déjà validée avec " + dejaValidees[i].note() + "\n";
      } 
    }

    virtual ~semestreInvalideErreur () throw() {}

    virtual const char* what () const throw() {
      return _msg.toStdString().c_str();
    }

    inline QList<UVEtudiant> dejaValidees () const { return _dejaValidees; }
  private:
    QString _msg;
    QList<UVEtudiant> _dejaValidees;

};

#endif
