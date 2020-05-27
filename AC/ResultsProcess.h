#pragma once
#include <QThread>
#include <QObject>
/**
*  @file     : MessageProcess.h
*  @version  : ver 1.0
*  @author   : Leon
*  @date     : 2020/5/21 14:38
*  @brief    : Used to process results messsage sent by the client
*/

/**
*@brief
*
* description
*/
class ResultsProcess :
	public QThread
{
	Q_OBJECT
public:
	ResultsProcess(QObject* parent = nullptr);
	~ResultsProcess();

protected:
	virtual void run()override;

signals:
	void running_error();

public slots:
	void stop() { running = false; }

private:
	bool running = false;
};