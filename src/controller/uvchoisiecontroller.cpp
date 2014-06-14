#include "uvchoisiecontroller.h"

UVChoisieController::UVChoisieController(UVEtudiant* uv, QUVChoisie* uvChoisie, QObject *parent) :
	QObject(parent), uv(uv), uvChoisie(uvChoisie)
{
	uvChoisie->setName(uv->tag());
	connect(this, SIGNAL(_remove()), uvChoisie, SLOT(deleteLater()));
	connect(this, SIGNAL(_remove()), this, SLOT(deleteLater()));
	connect(uvChoisie, SIGNAL(removeClicked()), this, SLOT(remove()));
}


void UVChoisieController::remove(){
	emit(removed(uv));
	emit(_remove());
}
