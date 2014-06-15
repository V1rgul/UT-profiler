#ifndef QUVCHOISIE_H
#define QUVCHOISIE_H

#include <QWidget>
#include "ui_quvchoisie.h"

class QUVChoisie : public QWidget
{
		Q_OBJECT

	public:
		explicit QUVChoisie(QWidget *parent = 0);
		void setName(QString s);
		void setNote(QString note);
		void addNotes(QStringList notes);

	signals:
		void removeClicked();
		void noteChanged(QString);
	public slots:
		void buttonRemoveClicked();
		void comboNoteChanged(QString);
	private:
		Ui::QUVChoisie ui;
};

#endif // QUVCHOISIE_H
