#include "DBManager.h"
#include "InformationCache.h"
#include "HardwareInfo.h"

#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <stdexcept>

QString DBManager::current_table = {};

DBManager::DBManager(const QString& connect_name)
	:connect_name(connect_name)
{
	open();
	if (db.tables().indexOf("Title") == -1)
	{
		add_title_table();
	}
}

DBManager::~DBManager()
{
	if (db.isOpen())
		db.close();
}

void DBManager::set_table(const QString& data)
{
	current_table = data;
}

void DBManager::open() throw(std::bad_exception)
{
	if (!db.isOpen())
	{
		db = QSqlDatabase::addDatabase("QSQLITE",connect_name);
		db.setDatabaseName("database.db");
	}	
	if (!db.open())
	{
		throw std::bad_exception();
	}
}

void DBManager::close()
{
	if (db.isOpen())
		db.close();
}


void DBManager::add_results_table() 
{
	QSqlQuery query(db);
	QString db_command = "CREATE TABLE " + current_table + "("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT,"
		"item TEXT,"
		"result TEXT);";
	bool ret = query.exec(db_command);
	if (!ret)
	{
		qDebug() << db.lastError();
		throw std::logic_error("Could not create title table in database.");
	}
}

void DBManager::set_title_content()
{
	QString insert_command = "INSERT INTO Title (datetime,cpu,motherboard,ram,gpu,os)"
		"VALUES (:datetime,:cpu,:motherboard,:ram,:gpu,:os)";
	auto& hardware_info = HardwareInfo::getInstance();
	QSqlQuery query(db);
	query.prepare(insert_command);
	query.bindValue(":datetime", current_table);
	query.bindValue(":cpu", QString::fromStdString(hardware_info.getCpuInfo()));
	query.bindValue(":motherboard", QString::fromStdString(hardware_info.getMotherboardInfo()));
	std::string ram;
	auto ram_list = hardware_info.getRAMInfo();
	for (int count = 0; count < ram_list.size(); ++count)
	{
		ram += ram_list[count].c_str();
		if (count != ram_list.size() - 1)
			ram += "\n";
	}
	query.bindValue(":ram", QString::fromStdString(ram));
	query.bindValue(":gpu", QString::fromStdString(hardware_info.getGPUInfo()));
	query.bindValue(":os", QString::fromLocal8Bit(hardware_info.getOSInfo().c_str()));
	if (!query.exec())
	{
		qDebug()<<query.lastError();
		throw std::logic_error("results value insert to database failed.");
	}
		


}

void DBManager::add_title_table() throw(std::logic_error)
{
	QSqlQuery query(db);
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
	if(current_table=="")
		throw std::logic_error("results table invaild.");
	QString insert_command = "INSERT INTO " + current_table + "(name,item,result)"
		"VALUES (:name,:item,:result)";
	QSqlQuery query(db); 
	query.prepare(insert_command);
	query.bindValue(":name", application_name);
	query.bindValue(":item", test_item_name);
	query.bindValue(":result", results);
	if (!query.exec())
		throw std::logic_error("results value insert to database failed.");
}

void DBManager::init_table()
{
	set_title_content();
	add_results_table();
}



