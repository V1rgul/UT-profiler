#include "qfiltrebranche.h"
#include <QtDebug>
#include <QCheckBox>

QFiltreBranche::QFiltreBranche(QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
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
	if(!sem.tryAcquire()) return;
	if(v == true){
		for(int i=0; i<ui.layoutBranches->count(); i++){
			QCheckBox *checkBox = qobject_cast<QCheckBox*>( ui.layoutBranches->itemAt(i)->widget() );
			if(checkBox != 0){
				checkBox->setChecked(false);
			} else {
				qCritical() << "qobject_cast<QCheckBox*> returned 0";
			}
		}
	}else{
		qDebug() << "radio toggled(false)";
	}
	emit(filterChanged(QStringList()));
	sem.release();
}

void QFiltreBranche::checkBox(bool v){
	Q_UNUSED(v);
	if(!sem.tryAcquire()) return;
	QStringList r;
	bool zeroChecked = true;
	for(int i=0; i<ui.layoutBranches->count(); i++){
		QCheckBox *checkBox = qobject_cast<QCheckBox*>( ui.layoutBranches->itemAt(i)->widget() );
		if(checkBox != 0){
			if(checkBox->isChecked()){
				r.append(checkBox->text());
				zeroChecked = false;
			}
		} else {
			qCritical() << "qobject_cast<QCheckBox*> returned 0";
		}
	}
	if(zeroChecked){
		ui.radioAll->setChecked(true);
	}
	emit(filterChanged(r));
	sem.release();
}
