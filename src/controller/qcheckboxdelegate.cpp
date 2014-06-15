#include "qcheckboxdelegate.h"
#include <QCheckBox>

QCheckBoxDelegate::QCheckBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *QCheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
   QCheckBox *editor = new QCheckBox(parent);

   return editor;
}

void QCheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   QString value = index.model()->data(index, Qt::EditRole).toString();

   QCheckBox *cBox = static_cast<QCheckBox*>(editor);
   cBox->setChecked( value=="X" );
}

void QCheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
   QCheckBox *cBox = static_cast<QCheckBox*>(editor);
   bool value = cBox->isChecked();

   model->setData(index, value?"X":" ", Qt::EditRole);
}

void QCheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
   editor->setGeometry(option.rect);
}
