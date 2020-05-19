#include "AC.h"
#include "ExecuteWidget.h"
#include "HelloWidget.h"

#include <QVBoxLayout>
AC::AC(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	main_layout_ = new QVBoxLayout(this);
	this->setLayout(main_layout_);
//	HelloWidget* widget = new HelloWidget(this);
	
	ExecuteWidget* widget = new ExecuteWidget(this);
	main_layout_->addWidget(widget);
}
