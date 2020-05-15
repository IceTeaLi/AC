#pragma once
/**
*  @file     : TestWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/14 11:26 
*  @brief    : Test window 
*/

#include <QWidget>

class QPushButton;
class ScriptsListWidget;
class QGridLayout;
class QStackedLayout;
/**
*@brief test window
*
* provide a user interface to test function
*/
class TestWidget :
	public QWidget
{
	Q_OBJECT
public:
	/**
	*@brief constructor
	*
	* TestWidget constructor
	*@param QWidget* -> parent window
	*/
	TestWidget(QWidget* parent = nullptr);
	/**
	*@brief destructor
	*
	* TestWidget destructor
	*/
	~TestWidget();

private:
	QPushButton* start_btn_;		///< start test button
	QPushButton* stop_btn_;		///< stop test button
	QPushButton* next_btn_;		///< next application button
	QPushButton* pause_btn_;		///< pause test button
	ScriptsListWidget* scripts_list_widget_;		///< show scripts list window
	QGridLayout* main_layout_;
	QStackedLayout* test_page_stackedlayout_;
private slots:
	/**
	*@brief start test slot function
	*
	* respond to the start button to start test
	*/
	void start();
	/**
	*@brief stop test slot function
	*
	* respond to the stop button to stop test
	*/
	void stop();
	/**
	*@brief pause test slot function
	*
	* respond to the pause button to pause test
	*/
	void pause();
	/**
	*@brief next applicatoin slot function
	*
	* respond to the next button to close current application ,and start next application
	*/
	void next();

};

