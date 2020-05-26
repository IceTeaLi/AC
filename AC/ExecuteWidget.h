#pragma once
/**
*  @file     : ExecuteWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/15 17:19 
*  @brief    : show execute functions 
*/
#include <qwidget.h>

class ExecuteListWidget;
class InformationWidget;
class QGridLayout;
class QHBoxLayout;
class QStackedLayout;
class QPushButton;
class ScriptsListWidget;
class Core;
/**
*@brief The window when the test is running.
*
* include a listwindow to show which scripts will be execute,and a textwindow to show running status.
*/
class ExecuteWidget :
	public QWidget
{
public:
	/**
	*@brief constructor
	*@param QWidget*
	*/
	ExecuteWidget(QWidget* parent = nullptr);
	~ExecuteWidget();

private:
	ScriptsListWidget* scripts_list_;			
	ExecuteListWidget* execute_list_;
	QStackedLayout* list_switcher_;

	InformationWidget* running_status_;
	QGridLayout* main_layout_;
	QHBoxLayout* btn_layout_;

	QPushButton* start_btn_;
	QPushButton* stop_btn_;
	QPushButton* pause_btn_;
	QPushButton* next_btn_;

	Core* core;

private slots:
	void start();
	void stop();
	void pause();
	

public slots:
	/**
	*@brief
	*
	* description
	*@param n1
	*/
	void get_execute_scripts(const QVector<QString>&);
	/**
	*@brief
	*
	* description
	*@param n1
    */
	void get_running_object_name(const QString&);

	void get_scripts_list_changed();
};

