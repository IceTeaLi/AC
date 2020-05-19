#include "ExecuteListWidget.h"

ExecuteListWidget::ExecuteListWidget(QWidget* parent)
	:QListWidget(parent)
{

}

void ExecuteListWidget::set_execute_list(const QVector<QString>& list)
{
	this->clear();
	for (auto& item : list)
	{
		this->addItem(new QListWidgetItem(item,this));
	}
}
void ExecuteListWidget::highlight_item(int row)
{
	if (row != 0)
	{
		auto last_item = this->item(row-1);
		auto item = this->item(row);
		last_item->setTextColor(item->textColor());
		item->setTextColor(QColor(Qt::red));
	}
	else
	{
		auto item = this->item(row);
		item->setTextColor(QColor(Qt::red));
	}
}
