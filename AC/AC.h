#pragma once
/**
*  @file AC.h 
*  @version ver 1.0 
*  @author Leon 
*  @date 2020/5/13 14:31 
*  @brief main window of application 
*/
#include <QtWidgets/QWidget>
#include "ui_AC.h"

class QListWidget;
class QStackedLayout;
class QVBoxLayout;
/**
*@brief main window class
*
* main window class£¬inherit by QWidget
*/
class AC : public QWidget
{
	Q_OBJECT

public:
	/**
	*@brief constructor
	*
	* constructor function
	*@param QWidget,point to parent widget£¬default value :nullptr[no parent widget]
	*/
	AC(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::ACClass ui;
	
	QListWidget* navigation_bar_;		///< show main functions of application 
	QStackedLayout* content_widget_;		///< show main contents 
	QVBoxLayout* main_layout_;		///< main layout
};
