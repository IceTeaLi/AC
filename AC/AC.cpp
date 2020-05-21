#include "AC.h"
#include "ExecuteWidget.h"
#include "HelloWidget.h"
#include "Server.h"
#include "NavBar.h"
#include "SettingsWidget.h"
#include <QHBoxLayout>
#include <QStackedLayout>

AC::AC(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	server = new Server(this);

	main_layout_ = new QHBoxLayout(this);
	this->setLayout(main_layout_);

	navigation_bar_ = new NavBar(this);
	content_widget_ = new QStackedLayout(this);

	HelloWidget* hello_widget = new HelloWidget(this);
	ExecuteWidget* execute_widget = new ExecuteWidget(this);
	SettingsWidget* settings_widget = new SettingsWidget(this);
	content_widget_->addWidget(hello_widget);
	content_widget_->addWidget(execute_widget);
	content_widget_->addWidget(settings_widget);
	main_layout_->addWidget(navigation_bar_);
	main_layout_->addLayout(content_widget_);
	connect(navigation_bar_, &NavBar::currentRowChanged, content_widget_, &QStackedLayout::setCurrentIndex);
}
