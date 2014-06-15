#include "quvchoisie.h"
#include "ui_quvchoisie.h"

QUVChoisie::QUVChoisie(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.buttonRemove, SIGNAL(clicked()), this, SLOT(buttonRemoveClicked()));
	connect(ui.comboNote, SIGNAL(currentTextChanged(QString)), this, SLOT(comboNoteChanged(QString)));
}

void QUVChoisie::buttonRemoveClicked(){
	emit(removeClicked());
}

void QUVChoisie::setName(QString s){
	ui.labelName->setText(s);
}

void QUVChoisie::setNote(QString note){
	ui.comboNote->setCurrentText(note);
}

void QUVChoisie::addNotes(QStringList notes){
	ui.comboNote->addItems(notes);
}

void QUVChoisie::comboNoteChanged(QString note){
	emit(noteChanged(note));
}
