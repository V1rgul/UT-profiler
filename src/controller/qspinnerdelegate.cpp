#include "qspinnerdelegate.h"
#include <QSpinBox>

QSpinnerDelegate::QSpinnerDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}


QWidget *QSpinnerDelegate::createEditor(QWidget *parent,
 const QStyleOptionViewItem &/* option */,
 const QModelIndex &/* index */) const
{
   QSpinBox *editor = new QSpinBox(parent);

   editor->setRange(0, 5);
   return editor;
}

void QSpinnerDelegate::setEditorData(QWidget *editor,
								 const QModelIndex &index) const
{
   int value = index.model()->data(index, Qt::EditRole).toInt();

   QSpinBox *sBox = static_cast<QSpinBox*>(editor);
   sBox->setValue(value);
}

void QSpinnerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
								const QModelIndex &index) const
{
   QSpinBox *sBox = static_cast<QSpinBox*>(editor);
   int value = sBox->value();

   model->setData(index, value, Qt::EditRole);
}

void QSpinnerDelegate::updateEditorGeometry(QWidget *editor,
 const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
   editor->setGeometry(option.rect);
}
