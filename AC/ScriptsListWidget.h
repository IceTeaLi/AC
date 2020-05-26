#pragma once
/**
*  @file     : ScriptsListWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/14 14:09 
*  @brief    : this class is used to show available scripts
*/


/**
*@brief dosplay available scripts window
*
* inherited from QListWidget and add checkbox to every items in this list
*/
#include <QListWidget>
#include <stdexcept>

class ScriptsListWidget :
	public QListWidget
{
public:	
	/**
	*@brief constructor
	*
	* constructor function
	*@param QWidget* -> Specify the parent class
	*/
	ScriptsListWidget(QWidget* parent = nullptr);
	/**
	*@brief destructor
	*
	* destructor class
	*/
	~ScriptsListWidget();

	/**
	*@brief Returns the selected items
	*@return const QVector<QString>
	*/
	const QVector<QString> get_checked_items() throw (std::invalid_argument);

private:

public slots:
	/**
	*@brief update scripts list
	*
	* This function is used to update the script list when the script directory changes or when the script in the directory changes
	*/
	void update();

	void item_clicked(QListWidgetItem* item);
};

