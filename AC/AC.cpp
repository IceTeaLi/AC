#include "AC.h"
#include "ExecuteWidget.h"
#include "HelloWidget.h"
#include "Server.h"
#include <QVBoxLayout>
AC::AC(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	main_layout_ = new QVBoxLayout(this);
	this->setLayout(main_layout_);
//	HelloWidget* widget = new HelloWidget(this);
	Server* server = new Server();
	server->show();
	ExecuteWidget* widget = new ExecuteWidget(this);
	main_layout_->addWidget(widget);
}
