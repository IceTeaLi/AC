#pragma once
/**
*  @file     : Core.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/20 10:10 
*  @brief    : The core module that controls the test script process
*/
#include <QThread>
#include <QVector>
#include <QString>

class Server;
class Process;
class MessageProcess;
class ResultsProcess;

class Core:public QThread
{
	Q_OBJECT

public:
	Core(QObject* parent=nullptr);
	~Core();

	inline void set_scripts_list(const QVector<QString> list);

protected:
	virtual void run();
	
public slots:
	void stop();
	void pause();
	void resume();
	void next();

private:
	QVector<QString> list_;
	QString current_scripts_ = {};
	bool running = false;
	Process* process_=nullptr;

	MessageProcess* msg_processer;
	ResultsProcess* result_processer;
signals:
	void emit_test_over(const QString&);
};


inline void Core::set_scripts_list(const QVector<QString> list)
{
	if (list.empty())
		throw std::invalid_argument("empty scripts list");
	list_ = list;
}