#pragma once
/**
*  @file     : ScriptsList.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/14 14:24 
*  @brief    : managing scripts
*/
#include <QString>
#include <QVector>
#include <stdexcept>
class ScriptsManager
{
public:
	/**
	*@brief manage scripts
	*
	* manage scripts,use singleten pattern ,cant be defined double times.
	*@return ScriptsManager, ScriptsManager's instance objects.
	*/
	static ScriptsManager& get_instance()
	{
		static ScriptsManager manger;
		return manger;
	}

	/**
	*@brief enum scripts
	*
	* Enumerates all script files from the specified directory
	*@param const std::string&,target directory.
	* If you pass in an illegal directory, such as an empty directory, an invaild_argument exception will be thrown.
	*@return std::vector<std::string>&,scripts lists 
	*/
	static const QVector<QString> get_scripts_list(const QString& directory) throw(std::invalid_argument);

private:
	/**
	*@brief constructor
	*
	* constructor
	*/
	ScriptsManager() {};
};