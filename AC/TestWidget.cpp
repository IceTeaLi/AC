#include "TestWidget.h"
#include "ScriptsListWidget.h"
#include <QGridLayout>
#include <QStackedLayout>
TestWidget::TestWidget(QWidget* parent)
	:QWidget(parent)
{
	main_layout_ = new QGridLayout(this);
	this->setLayout(main_layout_);

	test_page_stackedlayout_ = new QStackedLayout(this);
	scripts_list_widget_=new ScriptsListWidget(this);

	test_page_stackedlayout_->addWidget(scripts_list_widget_);
}

TestWidget::~TestWidget()
{
}

void TestWidget::start()
{
	test_page_stackedlayout_->setCurrentIndex(1);
}

void TestWidget::stop()
{
	test_page_stackedlayout_->setCurrentIndex(0);
}

void TestWidget::pause()
{
}

void TestWidget::next()
{
}
