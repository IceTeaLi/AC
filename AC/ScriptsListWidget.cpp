#include "ScriptsListWidget.h"
#include "ScriptsList.h"
#include "Settings.h"
#include "InformationCache.h"
ScriptsListWidget::ScriptsListWidget(QWidget* parent)
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	connect(this, &ScriptsListWidget::itemClicked, this, &ScriptsListWidget::item_clicked);
	update();
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
			list.push_back(this->item(count)->text()+"-auto.exe");
	}
	return list;
}

void ScriptsListWidget::item_clicked(QListWidgetItem* item)
{
	if (item->checkState() == Qt::CheckState::Checked)
		item->setCheckState(Qt::CheckState::Unchecked);
	else
		item->setCheckState(Qt::CheckState::Checked);
}

void ScriptsListWidget::update()
{
	this->clear();
	QVector<QString> list;
	try
	{
		list = ScriptsManager::get_scripts_list(QString::fromStdString(Settings::getInstance().get_scripts_folder()));
	}
	catch (std::exception& e)
	{
		auto& logger = InformationCache::get_instance();
		logger.insert(CONTROLLER_TAG + ERROR_TAG + e.what());
	}
	for (auto& name : list)
	{
		QListWidgetItem* item = new QListWidgetItem(name.mid(0,name.lastIndexOf("-auto.exe")),this);
		item->setCheckState(Qt::CheckState::Unchecked);
		this->addItem(item);
	}
}
