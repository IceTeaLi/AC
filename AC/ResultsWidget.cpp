#include "ResultsWidget.h"
#include "Settings.h"
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"

#include <QGridLayout>
#include <QPushButton>
#include <QTableView>
#include <QComboBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QHeaderView>
#include <QSqlError>
#include <QSqlRecord>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QtXlsx>
#include <QFileDialog>

QTXLSX_USE_NAMESPACE

ResultsWidget::ResultsWidget(QWidget* parent)
	:QWidget(parent)
{
	main_layout = new QGridLayout(this);
	table_layout = new QVBoxLayout(this);
	table_layout->setContentsMargins(0, 0, 0, 0);
	table_layout->setSpacing(0);
	this->setLayout(main_layout);

	results_file_selector = new QComboBox(this);
	data_viewer = new QTableView(this);
	title_viewer = new QTableView(this);
	title_viewer->setObjectName("title-table");
	data_viewer->setObjectName("data-table");
	table_layout->addWidget(title_viewer);
	table_layout->addWidget(data_viewer);
	table_layout->setStretch(0, 1);
	table_layout->setStretch(1, 3);

	choose_btn = new QPushButton(this);
	choose_btn->setText("refresh");
	connect(choose_btn, &QPushButton::clicked, this, &ResultsWidget::refresh_table_list);

	delete_btn = new QPushButton(this);
	delete_btn->setText(QString("delete"));
	connect(delete_btn, &QPushButton::clicked, this, &ResultsWidget::delete_results);


	db = QSqlDatabase::addDatabase("QSQLITE","results_widget");
	db.setDatabaseName("database.db");
	if (!db.open())
	{
		qDebug() << db.lastError();
	}
	
	title_model = new QSqlTableModel(this, db);
	data_model = new QSqlTableModel(this, db);
	refresh_table_list();
	
	export_btn = new QPushButton(this);;
	export_btn->setText(QString("export"));

	main_layout->addWidget(results_file_selector, 0, 0, 1, 5);
	main_layout->addWidget(choose_btn, 0, 5, 1, 1);
	main_layout->addWidget(delete_btn, 0, 6, 1, 1);
	main_layout->addLayout(table_layout, 1, 0, 7, 7);
	main_layout->addWidget(export_btn, 8, 6, 1, 1);
	connect(results_file_selector, &QComboBox::currentTextChanged, this, &ResultsWidget::show_data);
	connect(export_btn, &QPushButton::clicked, this, &ResultsWidget::export_results_to_xlsx);
}

ResultsWidget::~ResultsWidget()
{
}

void ResultsWidget::set_title_table(const QString& datetime)
{
	title_model->setTable("Title");
	title_model->setFilter(QObject::tr("datetime = '%1'").arg(datetime));
	title_model->select();
	QStandardItemModel* model = new QStandardItemModel();
	model->setColumnCount(2);
	
	model->setHeaderData(1, Qt::Horizontal, title_model->data(title_model->index(0, 0)).toString());
	model->setItem(0,0, new QStandardItem("CPU"));
	model->setItem(1, 0, new QStandardItem("MotherBoard"));
	model->setItem(2, 0, new QStandardItem("RAM"));
	model->setItem(3, 0, new QStandardItem("GPU"));
	model->setItem(4, 0, new QStandardItem("OS"));
	model->item(0, 0)->setTextAlignment(Qt::AlignCenter);
	model->item(1, 0)->setTextAlignment(Qt::AlignCenter);
	model->item(2, 0)->setTextAlignment(Qt::AlignCenter);
	model->item(3, 0)->setTextAlignment(Qt::AlignCenter);
	model->item(4, 0)->setTextAlignment(Qt::AlignCenter);
	for (int column = 0; column < title_model->columnCount(); column++)
	{
		model->setItem(column, 1, new QStandardItem(title_model->data(title_model->index(0,column+1)).toString()));
	}
	model->removeRow(model->rowCount());
	title_viewer->verticalHeader()->hide();

	title_viewer->setModel(model);
	title_viewer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	title_viewer->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//	title_viewer->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	title_viewer->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	title_viewer->show();
}

void ResultsWidget::delete_results()
{
	QString datetime = this->results_file_selector->currentText();
	title_model->setTable("Title");
	title_model->select();
	for (int row = 0; row < title_model->rowCount(); ++row)
	{
		if (title_model->record(row).value(0).toString() == datetime)
		{
			title_model->removeRow(row);
			QSqlQuery query(db);
			query.exec("DROP TABLE "+datetime);
			int row = results_file_selector->findText(datetime);
			if (row != -1)
				results_file_selector->removeItem(row);
			break;
		}
	}
}

void ResultsWidget::refresh_table_list()
{
	title_model->setTable("Title");
	title_model->select();

	for (int i = 0; i < title_model->rowCount(); ++i)
	{
		bool is_have = false;

		for (int row = 0; row < results_file_selector->count(); ++row)
		{
			if (title_model->record(i).value(0).toString() == results_file_selector->itemText(row))
			{
				is_have =true;
				break;
			}
		}
		if (is_have == false)
			this->results_file_selector->addItem(title_model->record(i).value(0).toString());
		else
			is_have = false;
	}	
}

void ResultsWidget::show_data(const QString& datetime)
{
	if (!datetime.isEmpty())
	{
		set_title_table(datetime);
		QString table = datetime;
		table.remove("[");
		table.remove("]");
		data_model->setTable(table);
		data_model->select();
		data_model->removeColumn(0);
		data_viewer->verticalHeader()->hide();
		data_viewer->setModel(data_model);
		data_viewer->show();
		data_viewer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		data_viewer->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		data_viewer->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	}

}

void ResultsWidget::export_results_to_xlsx()
{
	QString datetime = this->results_file_selector->currentText();
	QString results_folder_addr = QString::fromStdString(Settings::getInstance().get_results_folder());
	QString save_as = QFileDialog::getSaveFileName(this, "save as", results_folder_addr, tr("Xlsx (*.xlsx)"));
	QXlsx::Document xlsx(save_as);/*打开一个book1的文件*/

	/*硬件信息表格标题格式*/
	/*深颜色*/
	QXlsx::Format title_table_title_format;
	title_table_title_format.setBorderStyle(QXlsx::Format::BorderThin);
	title_table_title_format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
	title_table_title_format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
	title_table_title_format.setPatternBackgroundColor(QColor(155, 187, 89));

	/*硬件信息表格内容格式*/
	/*浅颜色*/
	QXlsx::Format title_color_data_format;
	title_color_data_format.setBorderStyle(QXlsx::Format::BorderThin);
	title_color_data_format.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
	title_color_data_format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
	title_color_data_format.setPatternBackgroundColor(QColor(235, 241, 222));
	/*根据当前表格标题填写总表头*/
	xlsx.write("A1", datetime);
	xlsx.mergeCells("A1:B1", title_table_title_format);
	/*查询导出表数据库数据*/
	title_model->setTable("Title");
	title_model->select();
	/*查询目标结果在数据库中的行值，用于访问其中数据*/
	int target_row = -1;
	for (int row = 0; row < title_model->rowCount(); ++row)
	{
		auto datetime_enum =title_model->record(row).value("datetime").toString();
		if (datetime_enum == datetime)
		{
			target_row = row;
		}
	}
	/*填写硬件信息数据*/
	xlsx.write("A2", "cpu", title_color_data_format);
	xlsx.write("A3", "motherboard", title_color_data_format);
	xlsx.write("A4", "ram", title_color_data_format);
	xlsx.write("A5", "gpu", title_color_data_format);
	xlsx.write("A6", "os", title_color_data_format);
	xlsx.write("B2", title_model->record(target_row).value("cpu").toString(), title_color_data_format);
	xlsx.write("B3", title_model->record(target_row).value("motherboard").toString(), title_color_data_format);
	xlsx.write("B4", title_model->record(target_row).value("ram").toString(), title_color_data_format);
	xlsx.write("B5", title_model->record(target_row).value("gpu").toString(), title_color_data_format);
	xlsx.write("B6", title_model->record(target_row).value("os").toString(), title_color_data_format);
//硬件信息导出结束
	int current_row = 7;
//导出测试结果

	QString last_name = "";
	for (int row = 0; row < data_model->rowCount(); ++row)
	{
		auto data_name = data_model->record(row).value("name").toString();

		if (data_name != last_name)
		{
			last_name = data_name;
			QString cell_pos = "A" + QString::number(current_row++);
			xlsx.write(cell_pos, data_name, title_table_title_format);
			xlsx.mergeCells("A"+ QString::number(current_row-1)+":B"+ QString::number(current_row-1), title_table_title_format);

			cell_pos = "A" + QString::number(current_row);
			auto item_name = data_model->record(row).value("item").toString();
			xlsx.write(cell_pos, item_name, title_color_data_format);
			cell_pos = "B" + QString::number(current_row++);
			auto results = data_model->record(row).value("result").toString();
			xlsx.write(cell_pos, results, title_color_data_format);
		}
		else
		{
			QString cell_pos = "A" + QString::number(current_row);
			auto item_name = data_model->record(row).value("item").toString();
			xlsx.write(cell_pos, item_name, title_color_data_format);
			cell_pos = "B" + QString::number(current_row++);
			auto results = data_model->record(row).value("result").toString();
			xlsx.write(cell_pos, results, title_color_data_format);
		}


	}
	xlsx.saveAs(save_as);
}