#pragma once
#include <QWidget>
#include <QSqlDatabase>
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
class QVBoxLayout;
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
	QVBoxLayout* table_layout;
	QSqlTableModel* title_model;
	QSqlTableModel* data_model;
	QSqlDatabase db;
	QPushButton* choose_btn;
	QPushButton* delete_btn;
	QPushButton* export_btn;

	void set_title_table(const QString& datetime);

public slots:
	void show_data(const QString& datetime);

	void delete_results();

private slots:
	void refresh_table_list();

	void export_results_to_xlsx();
};

