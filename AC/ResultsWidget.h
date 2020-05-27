#pragma once
#include <QWidget>
/**
*  @file     : ResultsWidget.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/22 9:53 
*  @brief    : used to display test results 
*/
class QTableView;
class QComboBox;
class QPushButton;
class QSqlTableModel;
class QGridLayout;
/**
*@brief results display window
*/
class ResultsWidget :
	public QWidget
{
public:
	ResultsWidget(QWidget* parent = nullptr);
	~ResultsWidget();

private:
	QTableView* data_viewer;
	QTableView* title_viewer;
	QComboBox* results_file_selector;
	QGridLayout* main_layout;
	QSqlTableModel* model;

	QPushButton* choose_btn;


public slots:
	void show_data(const QString& datetime);

private slots:
	void refresh_table_list();
};

