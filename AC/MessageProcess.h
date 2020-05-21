#pragma once
#include <qthread.h>
/**
*  @file     : MessageProcess.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/21 14:38 
*  @brief    : Used to process messages sent by the client 
*/

/**
*@brief 
*
* description
*/
class MessageProcess :
	public QThread
{
	Q_OBJECT
public:
	MessageProcess(QObject* parent = nullptr);
	~MessageProcess();

protected:
	virtual void run()override;

signals:
	void running_error();

public slots:
	void stop() { running = false; }

private:
	bool running = false;

	typedef struct StatusStr
	{
		std::string err = "[ERROR]";
		std::string good = "[GOOD]";
		std::string done = "[DONE]";
	}StatusStr;
	const StatusStr status_str_;
};

