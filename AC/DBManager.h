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
	DBManager(const QString& connect_name);
	~DBManager();

	static void set_table(const QString& data);

	void open() throw (std::bad_exception);
	void close();

	void insert(const QString& application_name, const QString& test_item_name, const QString& results);
	void init_table();

private:
	static QString current_table;
	const QString database_name = "database.db";
	const QString connect_name;
	QSqlDatabase db;

	void add_title_table() throw (std::bad_exception);
	void add_results_table()throw (std::bad_exception);
	void set_title_content();
};

