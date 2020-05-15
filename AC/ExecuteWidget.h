#pragma once
/**
*  @file     : ExecuteWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/15 17:19 
*  @brief    : show execute functions 
*/
#include <qwidget.h>

class QListView;
class QTextEdit;
class QHBoxLayout;
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
	*@brief
	*@param n1
	*/
	ExecuteWidget(QWidget* parent = nullptr);
	/**
	*@brief
	*/
	~ExecuteWidget();

private:
	QListView* scripts_list_;
	QTextEdit* running_status_;
	QHBoxLayout* main_layout_;

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
	/**
	*@brief
	*
	* description
	*@param n1
	*/
	void get_running_status(const QString&);
};

