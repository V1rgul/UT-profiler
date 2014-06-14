#include "qfiltrebranche.h"
#include <QtDebug>
#include <QCheckBox>

QFiltreBranche::QFiltreBranche(QWidget *parent) :
	QWidget(parent), sem(1), buttonGroup(this)
{
	ui.setupUi(this);
	buttonGroup.addButton(ui.radioAll);
	connect(ui.radioAll, SIGNAL(toggled(bool)), this, SLOT(allToggled(bool)));
}

void QFiltreBranche::addBranches(QStringList &listeBranches){
	sem.acquire();
	foreach(QString b, listeBranches){
		QCheckBox *c = new QCheckBox(b);
		connect(c, SIGNAL(toggled(bool)), this, SLOT(checkBox(bool)));
		ui.layoutBranches->addWidget(c);
	}
	sem.release();
}


void QFiltreBranche::allToggled(bool v){	
	qDebug() << "radio toggled(" << v << ")";
	if(!sem.tryAcquire()) return;
	qDebug() << "semaphore locked !";
	if(v == true){
		for(int i=0; i<ui.layoutBranches->count(); i++){
			QCheckBox *checkBox = qobject_cast<QCheckBox*>( ui.layoutBranches->itemAt(i)->widget() );
			if(checkBox != 0){
				checkBox->setChecked(false);
			} else {
				qCritical() << "qobject_cast<QCheckBox*> returned 0";
			}
		}
	}
	emit(filterChanged(QStringList()));
	sem.release();
}

void QFiltreBranche::checkRadio(bool v){
	qDebug() << "radioAll->setChecked(" << v << ")";
	buttonGroup.setExclusive(v);
	ui.radioAll->setChecked(v);
}

void QFiltreBranche::checkBox(bool v){
	Q_UNUSED(v);
	qDebug() << "checkBox toggled(" << v << ")";
	if(!sem.tryAcquire()) return;
	qDebug() << "semaphore locked !";
	QStringList r;
	bool zeroChecked = true, allChecked = true;
	for(int i=0; i<ui.layoutBranches->count(); i++){
		QCheckBox *checkBox = qobject_cast<QCheckBox*>( ui.layoutBranches->itemAt(i)->widget() );
		if(checkBox != 0){
			if(checkBox->isChecked()){
				r.append(checkBox->text());
				zeroChecked = false;
			}else{
				allChecked = false;
			}
		} else {
			qCritical() << "qobject_cast<QCheckBox*> returned 0";
		}
	}

	sem.release(); //release before to uncheck all checkBoxes with allTogled
	checkRadio(zeroChecked || allChecked);
	emit(filterChanged(r));	
}
