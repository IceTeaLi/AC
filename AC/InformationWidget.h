#pragma once
#include <qtextedit.h>
#include <thread>
#include <memory>
#include "InformationCache.h"
#include "MessageProcess.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
/**
*@brief InformationWidget used to display running information
*
* Inherited from QTextEdit
*/

class InformationWidget :
	public QTextEdit
{
public:
	InformationWidget(QWidget* parent = nullptr) :QTextEdit(parent)
	{
		this->setReadOnly(true);
		
		this->setContextMenuPolicy(Qt::CustomContextMenu);
		connect(this, &InformationWidget::customContextMenuRequested, this, &InformationWidget::context_menu);

		cache = &InformationCache::get_instance();
		std::thread message_reciver_thread([&] {
			while (!stop)
			{
				QString temp_string = QString::fromStdString(cache->get());	
				if (temp_string.contains(QString::fromStdString(ERROR_TAG)))
					this->append(QString("<font color=red>%1").arg(temp_string));
				else if(temp_string.contains(QString::fromStdString(GOOD_TAG)))
					this->append(QString("<font color=green>%1").arg(temp_string));
				else
					this->append(QString("<font color=yellow>%1").arg(temp_string));
				this->moveCursor(QTextCursor::End);
			}
			});
		message_reciver_thread.detach();
	}
	~InformationWidget()
	{
		stop = true;
		cache = nullptr;
	}
private:
	InformationCache* cache=nullptr;
	bool stop = false;

private slots:
	void context_menu(const QPoint& pos)
	{
		QMenu* menu = new QMenu(this);
		QAction* clear_action = new QAction("Clear", this);
		QAction* copy_action = new QAction("Copy", this);
		QAction* select_all_action = new QAction("SelectAll", this);
		menu->addAction(clear_action);
		menu->addAction(copy_action);
		menu->addAction(select_all_action);
		menu->move(cursor().pos());
		menu->show();

		connect(clear_action, &QAction::triggered, this, &InformationWidget::clear);
		connect(copy_action, &QAction::triggered, this, &InformationWidget::copy);
		connect(select_all_action, &QAction::triggered, this, &InformationWidget::selectAll);
	}
};

