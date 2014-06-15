#ifndef QUVPREVIEW_H
#define QUVPREVIEW_H

#include <QWidget>
#include "ui_quvpreview.h"

class QUVPreview : public QWidget
{
		Q_OBJECT

	public:
		explicit QUVPreview(QWidget *parent = 0);

	private:
		Ui::QUVPreview*ui;
};

#endif // QUVPREVIEW_H
