#ifndef QSPINNERDELEGATE_H
#define QSPINNERDELEGATE_H

#include <QItemDelegate>

class QSpinnerDelegate : public QItemDelegate
 {
	Q_OBJECT

 public:
	QSpinnerDelegate(QObject *parent = 0);

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // QSPINNERDELEGATE_H
