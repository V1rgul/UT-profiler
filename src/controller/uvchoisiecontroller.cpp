#include "uvchoisiecontroller.h"

UVChoisieController::UVChoisieController(UVEtudiant* uv, QUVChoisie* uvChoisie, QObject *parent) :
	QObject(parent), uv(uv), uvChoisie(uvChoisie)
{
	uvChoisie->setName(uv->tag());
	uvChoisie->addNotes(UVEtudiant::listeNotes());
	uvChoisie->setNote(uv->note());

	connect(this, SIGNAL(_remove()), uvChoisie, SLOT(deleteLater()));
	connect(this, SIGNAL(_remove()), this, SLOT(deleteLater()));
	connect(uvChoisie, SIGNAL(removeClicked()), this, SLOT(remove()));
	connect(uvChoisie, SIGNAL(noteChanged(QString)), this, SLOT(noteChanged(QString)));
}


void UVChoisieController::remove(){
	emit(removed(uv));
	emit(_remove());
}

void UVChoisieController::noteChanged(QString note){
	uv->note(note);
	emit(updated());
}
