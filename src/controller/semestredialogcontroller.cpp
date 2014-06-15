#include "semestredialogcontroller.h"
#include <QtDebug>
#include <QSortFilterProxyModel>
#include "model/uv.h"
#include "model/catalogue.h"
#include "uvchoisiecontroller.h"
#include "quvchoisie.h"


Q_DECLARE_METATYPE(UV *)

SemestreDialogController::SemestreDialogController(Etudiant* etudiant, Semestre* semestre, QObject* parent) :
	QObject(parent), etudiant(etudiant), semestre(semestre), semestreDialog(new QSemestreDialog), uvModel()
{
	spinDelegate = new QSpinnerDelegate(semestreDialog->getTableView());
	semestreDialog->getTableView()->setItemDelegateForColumn(0, spinDelegate);
	update();
	updateList();
	semestreDialog->getFiltreBranche()->addBranches(QStringList(QList<QString>::fromSet(Catalogue::instance()->cursus())));

	foreach(UVEtudiant* uv, semestre->uvs()){
		addUVChoisieToView(uv);
	}


	connect(semestreDialog, SIGNAL(saisonChanged()), this, SLOT(saisonChanged()));
	connect(semestreDialog, SIGNAL(yearChanged(int)), this, SLOT(yearChanged(int)));
	connect(semestreDialog->getFiltreBranche(), SIGNAL(filterChanged(QStringList)), this, SLOT(filterChanged(QStringList)));

	connect(semestreDialog, SIGNAL(rejected()), this, SLOT(deleteLater()));
	connect(semestreDialog, SIGNAL(rejected()), semestreDialog, SLOT(deleteLater()));	
}
SemestreDialogController::~SemestreDialogController(){
	delete spinDelegate;
	delete uvModel;
}

void SemestreDialogController::update(){
	semestreDialog->setSaison( (semestre->saison()==Semestre::AUTOMNE)? QString("A") : QString("P") );
	semestreDialog->setYear(semestre->annee());
	emit(updated());
}

void SemestreDialogController::saisonChanged(){
	Semestre::Saison newSaison = (semestre->saison()==Semestre::AUTOMNE)? Semestre::PRINTEMPS : Semestre::AUTOMNE;
	semestre->saison( newSaison );
	update();
	updateList();
}
void SemestreDialogController::yearChanged(int year){
	semestre->annee(year);
	//qDebug() << "semestre->annee(" << QString::number(year) << ")";
	update();
}

void SemestreDialogController::filterChanged(QStringList list){
	qDebug() << "filterChanged(" << list.join(", ") << ")[" << list.count() << "]";
	currentFilter = list;
	updateList();
}

void SemestreDialogController::updateList(){
	QMap<const UV*, unsigned int> uvs = etudiant->preferences(semestre->saison(), (currentFilter.count()==0)?0:&currentFilter );
	QStringList headers;
	headers << "Note" << "Tag" << "Titre" << "Cursus";

	QStandardItemModel* model = new QStandardItemModel(uvs.count(), headers.count(), this);
	model->setHorizontalHeaderLabels(headers);
	int row = 0;
	foreach(const UV* uv, uvs.keys()){
		QStandardItem* note = new QStandardItem(QString::number(uvs.value(uv)));
		note->setData(QVariant::fromValue( reinterpret_cast<quintptr>(uv) ));

		model->setItem(row, 0, note);
		model->setItem(row, 1, new QStandardItem(uv->tag()));
		model->setItem(row, 2, new QStandardItem(uv->titre()));
		model->setItem(row, 3, new QStandardItem(uv->cursus().join(",")));
		row++;
	}
	connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(preferenceUVChanged(QStandardItem*)));

	qDebug() << "model filled with" << row << "rows";
	model->sort(0, Qt::DescendingOrder);
	QAbstractItemModel* old = semestreDialog->swapModel(model);
	delete old;
}
void SemestreDialogController::preferenceUVChanged(QStandardItem * item){
	UV* uv = reinterpret_cast<UV*>( item->data().value<quintptr>() );
	if( uv == 0 ){
		qCritical() << "UV back cast failed ! : " << item->data().value<quintptr>() << ";";
	}
	etudiant->preference(uv, item->data(Qt::EditRole).toInt());
	qDebug() << "preference for uv'" << uv->tag() << "'changed to" << QString::number(etudiant->preference(uv));
}

void SemestreDialogController::addUVChoisieToView(UVEtudiant* uv){
	QUVChoisie* uvChoisie = new QUVChoisie();
	UVChoisieController* uvChosieController = new UVChoisieController(uv, uvChoisie, this);
	semestreDialog->addUVChoisie(uvChoisie);
	connect(uvChosieController, SIGNAL(removed(UVEtudiant*)), this, SLOT(uvChoisieRemoved(UVEtudiant*)));
	connect(uvChosieController, SIGNAL(updated()), this, SLOT(update()));
}

void SemestreDialogController::uvChoisieRemoved(UVEtudiant* uv){
	qDebug() << "UVChoisie removed(" << uv << ")";
	semestre->supprimerUv(uv->tag());
	update();
}



