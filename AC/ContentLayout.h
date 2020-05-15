#pragma once
/**
*  @file     : ContentLayout.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/13 15:21 
*  @brief    : Handles the parts of the main content display
*/

#include <QStackedLayout>

class HelloWidget;
class TestWidget;
class ResultsWidget;
class SettingsWidget;

/**
*@brief main content display class
*
* inherited from QStackedLayout, display all functions of application
*/
class ContentLayout :
	public QStackedLayout
{
	Q_OBJECT
public:
	/**
	*@brief constructor
	*
	* constructor function
	*@param QLayout* -> Specify the parent class
	*/
	ContentLayout(QLayout* parent = nullptr);
	/**
	*@brief destructor
	*
	* destructor class
	*/
	~ContentLayout();

private:

	HelloWidget* hello_widget_;		///< hello widget
	TestWidget* test_widget_;			///< test widget
	ResultsWidget* results_widget_;		///< result widget
	SettingsWidget* settings_widget_;		///< settings widget
};

