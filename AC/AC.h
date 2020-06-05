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

class NavBar;
class QStackedLayout;
class QHBoxLayout;
class Server;
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
	
	Server* server;

	NavBar* navigation_bar_;		///< show main functions of application 
	QStackedLayout* content_widget_;		///< show main contents 
	QHBoxLayout* main_layout_;		///< main layout

	/**
	*@brief used to init how widgets are laid out in an application's user interface.
	*
	* set navigation bar and stackedlayout position and set them automatically resize themselves.
	*/
	void init_layout();

	/**
	*@brief set up the application skin
	*
	* retrieve QSS from config.ini and call the global static function changskin() to set the skin
	*/
	void init_skin();

	/**
	*@brief initializes the navigation bar
	*
	* include hello widget button,test widget button,result widget button and settings widget button.
	*/
	void init_navigation_bar();
};
