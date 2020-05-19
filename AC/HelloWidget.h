#pragma once
/**
*  @file     : HelloWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/13 15:37 
*  @brief    : Hello window,  used to diplay basic hardware informatios.
*/
#include <qwidget.h>
#include <QMap>

class QLabel;
class QString;
class QTableWidget;
class QVBoxLayout;

/**
*@brief Hello window
*
* used to display basic hardware informations
*/
class HelloWidget :
	public QWidget
{
public:
	/**
	*@brief constructor
	*
	* constructor function
	*@param QWidget* -> Specify the parent class
	*/
	HelloWidget(QWidget* parent = nullptr);
	/**
	*@brief destructor
	*
	* destructor class
	*/
	~HelloWidget();
private:
	QLabel* title_;			///< show title
	QTableWidget* hardware_info_list_;		///< display some hardware informations 
	QVBoxLayout* main_layout_;			///< main layout
	
	/**
	*@brief get hardware informations
	*
	* Returns data provided to the window for display
	*@param std::map<QString,QString>, for get the data
	*/
	void get_hardware_info(QMap<QString,QString>* data);
	/**
	*@brief show hardware informations
	*
	* send data to QTableView for displays
	*@param const std::map<QString,QString>&, the data will be display
	*/
	void display_hardware_info(const QMap<QString, QString>& data);
};

