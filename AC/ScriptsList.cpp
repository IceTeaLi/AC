#include "ScriptsList.h"
#include <Windows.h>
#include <QDir>

const QVector<QString> ScriptsManager::get_scripts_list(const QString& directory) throw(std::invalid_argument)
{
	//��������·����//��\��β������ɾ����ͬһ����·����ʽ
	QString temp_dir = directory;
	if (temp_dir.back() == "\\" || temp_dir.back() == "/")
		temp_dir = temp_dir.left(temp_dir.size() - 1);

	QDir dir(temp_dir);
	// �ж��ļ����Ƿ����
	if(!dir.exists())
		throw std::invalid_argument("invalid directory.");
	// ���ü����ļ���׺
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
