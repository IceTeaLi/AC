#include "Settings.h"
#include "Settings.h"
#include <QSettings>
#include <stdexcept>

Settings::Settings()
	:config_file_("condig.ini")
{
	refresh(config_file_);
}

void Settings::refresh(const std::string& config_file)
{
	QSettings settings(QString::fromStdString(config_file), QSettings::IniFormat);

	default_skin_ = settings.value("skin/default").toString().toStdString();
	skins_folder_ = settings.value("folder/skins").toString().toStdString();
	scripts_folder_ = settings.value("folder/scripts").toString().toStdString();
	results_folder_ = settings.value("folder/results").toString().toStdString();
}

Settings& Settings::getInstance()
{
	static Settings settings;
	return settings;
}

Settings::~Settings()
{
}


void Settings::set_scripts_folder(const std::string& data) throw(std::invalid_argument)
{
	QSettings settings("config.ini", QSettings::IniFormat);
	if (data.empty())
		throw std::invalid_argument("empty scripts folder");

	{
		std::lock_guard<std::mutex> lock(scripts_dir_mtx_);
		settings.setValue("folder/scripts", QString::fromStdString(data));
	}
}

void Settings::set_results_folder(const std::string& data) throw(std::invalid_argument)
{
	QSettings settings("config.ini", QSettings::IniFormat);
	if (data.empty())
		throw std::invalid_argument("empty results folder");

	{
		std::lock_guard<std::mutex> lock(results_dir_mtx_);
		settings.setValue("folder/results", QString::fromStdString(data));
	}
}

void Settings::set_skins_folder(const std::string& data) throw(std::invalid_argument)
{
	QSettings settings("config.ini", QSettings::IniFormat);
	if (data.empty())
		throw std::invalid_argument("empty skins folder");

	{
		std::lock_guard<std::mutex> lock(skin_dir_mtx_);
		settings.setValue("folder/skins", QString::fromStdString(data));
	}
}

void Settings::set_default_skins(const std::string& data) throw(std::invalid_argument)
{
	QSettings settings("config.ini", QSettings::IniFormat);
	if (data.empty())
		throw std::invalid_argument("empty default skin");

	{
		std::lock_guard<std::mutex> lock(default_dir_mtx_);
		settings.setValue("skin/default", QString::fromStdString(data));
	}
}

const std::string& Settings::get_scripts_folder()
{
	return this->scripts_folder_;
}

const std::string& Settings::get_results_folder()
{
	return this->results_folder_;
}

const std::string& Settings::get_skins_folder()
{
	return this->skins_folder_;
}

const std::string& Settings::get_default_skins()
{
	return this->default_skin_;
}