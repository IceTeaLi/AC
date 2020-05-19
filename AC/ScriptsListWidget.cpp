#include "ScriptsListWidget.h"
#include "ScriptsList.h"
#include "Settings.h"
ScriptsListWidget::ScriptsListWidget(QWidget* parent)
{
	auto list = ScriptsManager::get_scripts_list(QString::fromStdString(Settings::getInstance().get_scripts_folder()));
	update(list);
}

ScriptsListWidget::~ScriptsListWidget()
{
}

const QVector<QString> ScriptsListWidget::get_checked_items()
{
	QVector<QString> list;
	for (int count = 0; count < this->count(); ++count)
	{
		if (this->item(count)->checkState() == Qt::CheckState::Checked)
			list.push_back(this->item(count)->text());
	}
	return list;
}

void ScriptsListWidget::update(const QVector<QString>& list)
{
	for (auto& name : list)
	{
		QListWidgetItem* item = new QListWidgetItem(name,this);
		item->setCheckState(Qt::CheckState::Unchecked);
		this->addItem(item);
	}
}
