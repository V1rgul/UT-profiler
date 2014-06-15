#include "qcheckboxdelegate.h"
#include <QCheckBox>
#include <QtDebug>
#include <QEvent>

QCheckBoxDelegate::QCheckBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *QCheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
	Q_UNUSED(parent);
   return 0;
}

bool QCheckBoxDelegate::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index){
	Q_UNUSED(option);
	if(event->type() == QEvent::MouseButtonDblClick){
		model->setData(index, "X", Qt::EditRole);
		event->accept();
		return true;
	}
	return false;
}

void QCheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
   editor->setGeometry(option.rect);
}
