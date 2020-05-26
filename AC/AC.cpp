#include "AC.h"
#include "ExecuteWidget.h"
#include "HelloWidget.h"
#include "Server.h"
#include "SettingsWidget.h"
#include "ResultsWidget.h"
#include "Settings.h"
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QListWidget>

AC::AC(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setObjectName("main");
	this->setContentsMargins(0, 0, 0, 0);

	init_skin();
	server = new Server(this);

	main_layout_ = new QHBoxLayout(this);

	this->setLayout(main_layout_);

	navigation_bar_ = new QListWidget(this);
	navigation_bar_->setObjectName("navigationbar");
	init_navigation_bar();
	content_widget_ = new QStackedLayout(this);

	HelloWidget* hello_widget = new HelloWidget(this);
	ExecuteWidget* execute_widget = new ExecuteWidget(this);
	ResultsWidget* results_widget = new ResultsWidget(this);
	SettingsWidget* settings_widget = new SettingsWidget(this);
	connect(settings_widget, &SettingsWidget::emitScriptsFolderChanged, execute_widget, &ExecuteWidget::get_scripts_list_changed);

	content_widget_->addWidget(hello_widget);
	content_widget_->addWidget(execute_widget);
	content_widget_->addWidget(results_widget);
	content_widget_->addWidget(settings_widget);

	init_layout();

	connect(navigation_bar_, &QListWidget::currentRowChanged, content_widget_, &QStackedLayout::setCurrentIndex);
}

void AC::init_layout()
{
	main_layout_->setMargin(0);
	main_layout_->setContentsMargins(0, 0, 0, 0);

	main_layout_->addWidget(navigation_bar_);
	main_layout_->addLayout(content_widget_);
	main_layout_->setStretchFactor(navigation_bar_, 1);
	main_layout_->setStretchFactor(content_widget_, 3);
}

void AC::init_skin()
{
	auto& settings = Settings::getInstance();
	changeSkin(QString::fromStdString(settings.get_skins_folder() + settings.get_default_skins() + ".qss"));

}

void AC::init_navigation_bar()
{
	QListWidgetItem* hello_item = new QListWidgetItem(QString("Hello"), navigation_bar_);
	QListWidgetItem* test_item = new QListWidgetItem(QString("Tests"), navigation_bar_);
	QListWidgetItem* result_item = new QListWidgetItem(QString("Results"), navigation_bar_);
	QListWidgetItem* settings_item = new QListWidgetItem(QString("Settings"), navigation_bar_);
	hello_item->setTextAlignment(Qt::AlignCenter);
	test_item->setTextAlignment(Qt::AlignCenter);
	result_item->setTextAlignment(Qt::AlignCenter);
	settings_item->setTextAlignment(Qt::AlignCenter);
	navigation_bar_->addItem(hello_item);
	navigation_bar_->addItem(test_item);
	navigation_bar_->addItem(result_item);
	navigation_bar_->addItem(settings_item);
}
