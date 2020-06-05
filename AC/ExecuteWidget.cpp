#include "ExecuteWidget.h"
#include "ScriptsListWidget.h"
#include "ExecuteListWidget.h"
#include "InformationWidget.h"
#include "MessageCache.h"
#include "Core.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTime>

ExecuteWidget::ExecuteWidget(QWidget* parent)
	:QWidget(parent)
{
	main_layout_ = new QGridLayout(this);
	this->setLayout(main_layout_);

	list_switcher_ = new QStackedLayout(this);
	scripts_list_ = new ScriptsListWidget(this);
	execute_list_ = new ExecuteListWidget(this);
	list_switcher_->addWidget(scripts_list_);
	list_switcher_->addWidget(execute_list_);

	running_status_ = new InformationWidget(this);

	start_btn_ = new QPushButton(QString("start"),this);
	pause_btn_ = new QPushButton(QString("pause"), this);
	next_btn_ = new QPushButton(QString("next"), this);
	stop_btn_ = new QPushButton(QString("stop"), this);
	clear_btn_ = new QPushButton(QString("clear"), this);

	btn_layout_ = new QHBoxLayout(this);
	btn_layout_->addWidget(clear_btn_);
	btn_layout_->addStretch(1);
	btn_layout_->addWidget(start_btn_);
	btn_layout_->addWidget(pause_btn_);
	btn_layout_->addWidget(next_btn_);
	btn_layout_->addWidget(stop_btn_);

	core = new Core(this);

	connect(start_btn_, &QPushButton::clicked, this, &ExecuteWidget::start);
	connect(pause_btn_, &QPushButton::clicked, this, &ExecuteWidget::pause);
	connect(next_btn_, &QPushButton::clicked, core, &Core::next);
	connect(stop_btn_, &QPushButton::clicked, core, &Core::stop);
	connect(stop_btn_, &QPushButton::clicked, this, &ExecuteWidget::stop);
	connect(clear_btn_, &QPushButton::clicked, this, &ExecuteWidget::clear);

	main_layout_->addLayout(list_switcher_, 0, 0);
	main_layout_->setSpacing(10);
	main_layout_->addWidget(running_status_,0,1);
	main_layout_->addLayout(btn_layout_, 3, 1);
	main_layout_->setColumnStretch(0, 1);
	main_layout_->setColumnStretch(1, 3);

	connect(core, &Core::emit_test_over, this, &ExecuteWidget::emit_test_over);
}

ExecuteWidget::~ExecuteWidget()
{
	if (core->isRunning())
	{
		core->quit();
		delete core;
	}
}

void ExecuteWidget::start()
{
	QVector<QString> list = this->scripts_list_->get_checked_items();
	this->execute_list_->set_execute_list(list);
	this->list_switcher_->setCurrentWidget(this->execute_list_);

	
	core->set_scripts_list(list);
	core->start();
}



void ExecuteWidget::stop()
{
	this->list_switcher_->setCurrentWidget(this->scripts_list_);
}

void ExecuteWidget::pause()
{
	QString pause_btn_text = pause_btn_->text();
	if (pause_btn_text == "pause")
	{
		core->pause();
		pause_btn_->setText(QString("resume"));
	}
	else
	{
		core->resume();
		pause_btn_->setText(QString("pause"));
	}
}

void ExecuteWidget::clear()
{
	this->running_status_->clear();
}

void ExecuteWidget::get_test_over(const QString& data)
{
	list_switcher_->setCurrentWidget(scripts_list_);
	emit emit_test_over(data);

}

void ExecuteWidget::get_running_object_name(const QString&)
{
}

void ExecuteWidget::get_scripts_list_changed()
{
	this->scripts_list_->update(); 
}

