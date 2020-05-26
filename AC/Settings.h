#pragma once
/**
*  @file     : Settings.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/15 10:50 
*  @brief    : store application settings 
*/
#include <string>
#include <mutex>
#include "InformationCache.h"
/**
*@brief manage objects related to Settings
*
* find or modify the Settings,single instance
*/
class Settings
{
	std::mutex skin_dir_mtx_;			///< Used to lock skin dir data during modification operations
	std::mutex scripts_dir_mtx_;			///< Used to lock scripts dir data during modification operations
	std::mutex results_dir_mtx_;			///< Used to lock results dir data during modification operations
	std::mutex default_dir_mtx_;			///< Used to lock default skin data during modification operations

	const std::string config_file_ ;			///< store config file address

	std::string default_skin_;			///< store default skin address
	std::string scripts_folder_;			///< store scripts dir address
	std::string results_folder_;			///< store results dir address
	std::string skins_folder_;			///< store skin dir address

public:
	/**
	*@brief get seetings instances
	*
	* get seetings instances
	*/
	static Settings& getInstance();
	~Settings();

	/**
	*@brief set the script directory path
	*
	* If you enter an illegal path, an exception is thrown
	*@param const std::string&: directory address
	*/
	void set_scripts_folder(const std::string&) throw(std::invalid_argument);
	/**
	*@brief set the results directory path
	*
	* If you enter an illegal path, an exception is thrown
	*@param const std::string&: directory address
	*/
	void set_results_folder(const std::string&) throw(std::invalid_argument);
	/**
	*@brief set the skins directory path
	*
	* If you enter an illegal path, an exception is thrown
	*@param const std::string&: directory address
	*/
	void set_skins_folder(const std::string&) throw(std::invalid_argument);
	/**
	*@brief set the default skin path
	*
	* If you enter an illegal path, an exception is thrown
	*@param const std::string&: skin address
	*/
	void set_default_skins(const std::string&) throw(std::invalid_argument);

	/**
	*@brief get the scripts directory path
	*/
	const std::string& get_scripts_folder();
	/**
	*@brief set the results directory path
	*/
	const std::string& get_results_folder();
	/**
	*@brief set the skins directory path
	*/
	const std::string& get_skins_folder();
	/**
	*@brief set the default skin path
	*/
	const std::string& get_default_skins();

private:
	Settings();

	void refresh(const std::string& config_file);
};
