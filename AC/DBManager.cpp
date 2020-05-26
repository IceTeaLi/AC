#include "DBManager.h"
#include "InformationCache.h"

#include <QVariant>
#include <QSqlQuery>
#include <stdexcept>
DBManager::DBManager()
{
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("database.db");
	if (!database.open())
	{
		throw std::invalid_argument("QSqlDatabase can not open database.db");
	}
	if (database.tables().indexOf("Title") == -1)
	{
		add_title_table();
	}
}


void DBManager::open()
{
}

void DBManager::close()
{
}

void DBManager::add_results_table() 
{
	QSqlQuery query(database);
	QString db_command = "CREATE TABLE " + current_title + "("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT,"
		"item TEXT,"
		"result TEXT);";
	bool ret = query.exec(db_command);
	if (!ret)
		throw std::logic_error("Could not create title table in database.");
}

void DBManager::add_title_table() throw(std::logic_error)
{
	QSqlQuery query(database);
	bool ret = query.exec("CREATE TABLE Title("
		"datetime TEXT PRIMARY KEY,"
		"cpu TEXT,"
		"motherboard TEXT,"
		"ram TEXT,"
		"gpu TEXT,"
		"os TEXT);");
	if (!ret)
		throw std::logic_error("Could not create title table in database.");
}


void DBManager::insert(const QString& application_name, const QString& test_item_name, const QString& results)
{
	QString insert_command = "INSERT INTO " + current_title + "(name,item,result)"
		"VALUES (:name,:item,:result)";
	QSqlQuery query(database);
	query.prepare(insert_command);
	query.bindValue(":name", application_name);
	query.bindValue(":item", test_item_name);
	query.bindValue(":result", results);
	if (!query.exec())
		throw std::logic_error("results value insert to database failed.");
}

QVector<ResultsData> DBManager::get_results(const QString& title)
{
	QString insert_command = "SELECT * FROM " + current_title;
	QSqlQuery query(database);
	query.prepare(insert_command);
	QVector<ResultsData> temp;
	if (!query.exec())
		throw std::logic_error("could not selected results table");
	while (query.next())
	{
		
		ResultsData temp_result_data = { query.value(0).toString(), query.value(1).toString(), query.value(2).toString() };
		temp.push_back(temp_result_data);
	}

	return temp;
}

const Title DBManager::get_title(const QString& title)
{
	QString insert_command = "SELECT " + current_title + " FROM Title";
	QSqlQuery query(database);
	if (!query.exec())
		throw std::logic_error("could not selected title table");
	Title temp = { query.value(0).toString(),
		query.value(1).toString(),
		query.value(2).toString(),
		query.value(3).toString(),
		query.value(4).toString(),
		query.value(5).toString() };
}


