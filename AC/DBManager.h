#pragma once
/**
*  @file     : DBManager.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/26 16:38 
*  @brief    : manage the database which store the results.  
*/
#include <QString>
#include <QVector>
#include <QSqlDatabase>

typedef struct ResultsData
{
	QString application_name;
	QString test_item_name;
	QString score;
}ResultsData;

typedef struct Title
{
	QString datetime;
	QString cpu;
	QString motherboard;
	QString ram;
	QString gpu;
	QString os;
}Title;

class DBManager
{
public:
	static DBManager& get_instance()
	{
		static DBManager manager;
		return manager;
	}
	~DBManager()
	{
		if (database.isOpen())
			database.close();
	}



	inline void setTitle(const QString & title);
	void insert(const QString & application_name, const QString & test_item_name, const QString & results);

	QVector<ResultsData> get_results(const QString & title);
	const Title get_title(const QString& title);

private:
	DBManager();
	QString current_title;
	QSqlDatabase database;

	void open();
	void close();
	void add_title_table() throw (std::logic_error);
	void add_results_table()throw (std::logic_error);
};

inline void DBManager::setTitle(const QString& title)
{
	current_title = title;
}
