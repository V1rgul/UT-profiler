#ifndef ETUDIANTCONTROLLER_H
#define ETUDIANTCONTROLLER_H

#include <QObject>
#include <QWidget>
#include "model/etudiant.h"

class EtudiantController : public QObject
{
		Q_OBJECT
	public:
		EtudiantController(QWidget* tabEtudiant, Etudiant etudiant, QObject *parent = 0);
		EtudiantController(QWidget* tabEtudiant, QObject *parent = 0);

	signals:

	public slots:
		void nameChanged(QString name, QString surname);
	private:
		QWidget* tabEtudiant;
		Etudiant* etudiant;
};

#endif // ETUDIANTCONTROLLER_H
