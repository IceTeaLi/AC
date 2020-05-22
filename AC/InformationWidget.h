#pragma once
#include <qtextedit.h>
#include <thread>
#include <memory>
#include "InformationCache.h"
#include "MessageProcess.h"
#include <QDebug>
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

		cache = &InformationCache::get_instance();
		std::thread message_reciver_thread([&] {
			while (!stop)
			{
				QString temp_string = QString::fromStdString(cache->get());	
				if (temp_string.contains(QString::fromStdString(ERROR_TAG)))
				{
					this->append(QString("<font color=red>%1").arg(temp_string));
				}else
					this->append(QString("<font color=green>%1").arg(temp_string));
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
};

