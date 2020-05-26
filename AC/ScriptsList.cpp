#include "ScriptsList.h"
#include <Windows.h>
#include <QDir>

const QVector<QString> ScriptsManager::get_scripts_list(const QString& directory) throw(std::invalid_argument)
{
	//如果传入的路径以//或\结尾，则将其删除，同一传入路径格式
	QString temp_dir = directory;
	if (temp_dir.back() == "\\" || temp_dir.back() == "/")
		temp_dir = temp_dir.left(temp_dir.size() - 1);

	QDir dir(temp_dir);
	// 判断文件夹是否存在
	if(!dir.exists())
		throw std::invalid_argument("Failed to get script list. Specified folder does not exist ");
	// 设置检索文件后缀
	QStringList nameFilters;
	nameFilters << "*-auto.exe";
	QFileInfoList files = dir.entryInfoList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);

	QVector<QString> list;
	for (auto& c : files)
	{
		list.push_back(c.fileName());
	}
	return list;
}
