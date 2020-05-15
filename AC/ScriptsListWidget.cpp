#include "ScriptsListWidget.h"
#include "ScriptsList.h"
#include "Settings.h"
ScriptsListWidget::ScriptsListWidget(QWidget* parent)
{
	auto& manger = ScriptsManager::get_instance();
	update(manger.get_scripts_list(QString::fromStdString(Settings::getInstance().get_scripts_folder())));
}

ScriptsListWidget::~ScriptsListWidget()
{
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
