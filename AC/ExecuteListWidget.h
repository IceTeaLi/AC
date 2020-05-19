#pragma once
/**
*  @file     : ExecuteListWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/19 17:52 
*  @brief    : manage execute list window 
*/
#include <QListWidget>
#include <QVector>
#include <QString>
/**
*@brief Shows the scripts list that is expected to be executed
*/
class ExecuteListWidget:public QListWidget
{
public:
	/**
	*@brief constructor
	*/
	ExecuteListWidget(QWidget* parent = nullptr);
private:

public slots:
	/**
	*@brief set the list of scripts to display on the window
	*@param const QVector<QString>&: scripts list vector
	*/
	void set_execute_list(const QVector<QString>& list);
	/**
	*@brief highlight current running script
	*@param int :script id
	*/
	void highlight_item(int);
};

