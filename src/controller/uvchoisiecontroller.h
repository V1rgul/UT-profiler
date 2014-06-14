#ifndef UVCHOISIECONTROLLER_H
#define UVCHOISIECONTROLLER_H

#include <QObject>
#include "quvchoisie.h"
#include "model/uvEtudiant.h"

class UVChoisieController : public QObject
{
		Q_OBJECT
	public:
		explicit UVChoisieController(UVEtudiant* uv, QUVChoisie* uvChoisie, QObject *parent = 0);

	signals:
		void _remove();
		void removed(UVEtudiant*);
	public slots:
		void remove();

	private:
		UVEtudiant* uv;
		QUVChoisie* uvChoisie;

};

#endif // UVCHOISIECONTROLLER_H
