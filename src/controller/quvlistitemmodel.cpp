#include "quvlistitemmodel.h"
#include "model/catalogue.h"

QUVListItemModel::QUVListItemModel(QObject *parent) :
    QStandardItemModel(parent)
{
}


virtual QVariant QUVListItemModel::data ( const QModelIndex & index, int role = Qt::DisplayRole ) const{
	if(role == Qt::ToolTipRole){
		Catalogue::instance()
	}
}
