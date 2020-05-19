#include "ExecuteWidget.h"
#include "ScriptsListWidget.h"
#include "ExecuteListWidget.h"

#include <QGridLayout>
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

	running_status_ = new QTextEdit(this);
	running_status_->setReadOnly(true);

	start_btn_ = new QPushButton(QString("start"),this);
	pause_btn_ = new QPushButton(QString("pause"), this);
	next_btn_ = new QPushButton(QString("next"), this);
	stop_btn_ = new QPushButton(QString("stop"), this);

	connect(start_btn_, &QPushButton::clicked, this, &ExecuteWidget::start);


	main_layout_->addLayout(list_switcher_, 0, 0, 3, 1);
	main_layout_->addWidget(running_status_,0,1,3,4);
	main_layout_->setRowStretch(3, 1);
	main_layout_->addWidget(start_btn_, 3, 1, 1, 1);
	main_layout_->addWidget(pause_btn_, 3, 2, 1, 1);
	main_layout_->addWidget(next_btn_, 3, 3, 1, 1);
	main_layout_->addWidget(stop_btn_, 3, 4, 1, 1);
}

ExecuteWidget::~ExecuteWidget()
{
}

void ExecuteWidget::start()
{
	QVector<QString> list = this->scripts_list_->get_checked_items();
	this->execute_list_->set_execute_list(list);
	this->list_switcher_->setCurrentWidget(this->execute_list_);
}



void ExecuteWidget::stop()
{
	this->list_switcher_->setCurrentWidget(this->scripts_list_);
}

void ExecuteWidget::pause()
{
}

void ExecuteWidget::next()
{
}

void ExecuteWidget::get_running_object_name(const QString&)
{
}

void ExecuteWidget::append_status(const QString& status_str)
{
	QTime time;
	QString time_str = "[" + time.currentTime().toString("hh:mm:ss") + "]";
	this->running_status_->append(time_str + status_str);
}

void ExecuteWidget::get_running_status(const QString& status_str)
{
	append_status(status_str);
}

