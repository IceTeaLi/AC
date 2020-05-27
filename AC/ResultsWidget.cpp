#include "ResultsWidget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QComboBox>
#include <QSqlTableModel>
#include <QSqlRecord>
ResultsWidget::ResultsWidget(QWidget* parent)
	:QWidget(parent)
{
	main_layout = new QGridLayout(this);
	this->setLayout(main_layout);

	results_file_selector = new QComboBox(this);
	data_viewer = new QTableView(this);
	title_viewer = new QTableView(this);
	choose_btn = new QPushButton(this);
	choose_btn->setText("refresh");
	connect(choose_btn, &QPushButton::clicked, this, &ResultsWidget::refresh_table_list);

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("database.db");
	db.open();
	model = new QSqlTableModel(this, db);

	main_layout->addWidget(results_file_selector, 0, 0, 1, 4);
	main_layout->addWidget(choose_btn, 0, 4, 1, 1);
	main_layout->addWidget(data_viewer, 1, 0, 5, 5);

	refresh_table_list();

	connect(results_file_selector, &QComboBox::currentTextChanged, this, &ResultsWidget::show_data);
}

ResultsWidget::~ResultsWidget()
{
}

void ResultsWidget::refresh_table_list()
{
	model->setTable("Title");
	model->select();
	model->submit();
	this->results_file_selector->clear();
	for (int i = 0; i < model->rowCount(); ++i)
	{
		this->results_file_selector->addItem(model->record(i).value(0).toString());
	}
	
}

void ResultsWidget::show_data(const QString& datetime)
{
	model->setTable(datetime);
	model->select();
	model->submit();
		data_viewer->setModel(model);
	data_viewer->show();
}