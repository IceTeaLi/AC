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
				qDebug() << temp_string;
				this->append(temp_string);
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

