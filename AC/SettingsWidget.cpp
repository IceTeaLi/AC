#include "SettingsWidget.h"
#include "Settings.h"

#include <QDirIterator>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

SettingsWidget::SettingsWidget(QWidget* parent)
	:QWidget(parent)
{
	mainLayout = new QGridLayout(this);
	this->setLayout(mainLayout);

	skinsLayout = new Skins(this);
	scriptsFolderLayout = new FolderSetting("scripts", u8"脚本目录",this);
	resultsFolderLayout = new FolderSetting("results", u8"结果目录", this);
	skinsFolderLayout = new FolderSetting("skins", u8"皮肤目录", this);
	connect(skinsFolderLayout, &FolderSetting::clicked, skinsLayout, &Skins::getSkinsFolderChanged);
	connect(scriptsFolderLayout, &FolderSetting::clicked, this, &SettingsWidget::ScriptsFolderChanged);
	mainLayout->addLayout(skinsLayout,0,0);
	mainLayout->addLayout(scriptsFolderLayout, 1, 0);
	mainLayout->addLayout(resultsFolderLayout, 2, 0);
	mainLayout->addLayout(skinsFolderLayout, 3, 0);

}

SettingsWidget::~SettingsWidget()
{

}

Skins::Skins(QWidget* parent)
{
	label = new QLabel(parent);
	label->setText(QString(u8"主题"));

	combox = new QComboBox(parent);
	refresh();
	Settings& settings = Settings::getInstance();

	combox->setCurrentText(QString::fromStdString(settings.get_default_skins()));

	chooseBtn = new QPushButton(parent);
	chooseBtn->setText(QString(u8"选择"));

	this->addWidget(label, 0, Qt::AlignCenter);
	this->addWidget(combox, 400);
	this->addWidget(chooseBtn, 0);

	connect(chooseBtn, &QPushButton::clicked, this, &Skins::chooseBtnClicked);
}
Skins::~Skins()
{

}
void Skins::scanQSSFile(const QString& folder, QStringList& list)
{
	QStringList filter;
	filter << "*.qss";
	QDirIterator it(folder, filter, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
	while (it.hasNext())
	{
		it.next();
		list << it.fileName().remove(".qss");
	}
}
void Skins::refresh()
{
	QStringList list;
	auto& settings = Settings::getInstance();

	scanQSSFile(QString::fromStdString(settings.get_skins_folder()), list);
	combox->clear();
	for (auto& c : list)
	{
		combox->addItem(c);
	}
}
void Skins::chooseBtnClicked()
{
	//获取全局设置中的皮肤文件夹路径
	auto& settings = Settings::getInstance();

	//获取combobox中的当前选项
	QString qssFilename = this->combox->currentText();
	//如果combobox不为空，则调用改变皮肤func
	if (!qssFilename.isEmpty())
	{
		changeSkin(QString::fromStdString(settings.get_skins_folder()) + qssFilename + ".qss");
		settings.set_default_skins(qssFilename.toStdString());
	}

}

FolderSetting::FolderSetting(const QString& _value, const QString& _label, QWidget* _parent)
	:settingConfigValue(_value), QHBoxLayout(_parent)
{
	label = new QLabel(_parent);
	label->setText(_label);

	edit = new QLineEdit(_parent);
	auto& settings = Settings::getInstance();
	if (settingConfigValue == "scripts")
		edit->setText(QString::fromStdString(settings.get_scripts_folder()));
	if (settingConfigValue == "results")
		edit->setText(QString::fromStdString(settings.get_results_folder()));
	if (settingConfigValue == "skins")
		edit->setText(QString::fromStdString(settings.get_skins_folder()));

	chooseBtn = new QPushButton(_parent);
	chooseBtn->setText(QString(u8"确定"));

	searchFolderBtn = new QPushButton(_parent);
	searchFolderBtn->setText(QString(u8"查找"));



	this->addWidget(label, 0);
	this->addWidget(edit, 400);
	this->addWidget(searchFolderBtn, 0);
	this->addWidget(chooseBtn, 0);

	connect(searchFolderBtn, &QPushButton::clicked, this, &FolderSetting::searchFolderBtnClicked);
	connect(chooseBtn, &QPushButton::clicked, this, &FolderSetting::chooseBtnClicked);
}
FolderSetting::~FolderSetting()
{
}
void FolderSetting::chooseBtnClicked()
{
	auto& settings = Settings::getInstance();
	try
	{
		QString data = edit->text();
		QDir info(data);
		if (!info.exists() || edit->text().isEmpty())
			throw std::invalid_argument("The address doesnt exist");
		if (settingConfigValue == "scripts")
			settings.set_scripts_folder(edit->text().toStdString());
		if (settingConfigValue == "results")
			settings.set_results_folder(edit->text().toStdString());
		if (settingConfigValue == "skins")
			settings.set_skins_folder(edit->text().toStdString());
		QMessageBox ok;
		ok.setText(settingConfigValue + " folder changed");
		ok.exec();
		emit clicked();
	}
	catch (std::exception& e)
	{
		QMessageBox box;
		box.setText((e.what()));
		box.exec();
	}
}
void FolderSetting::searchFolderBtnClicked()
{
	QString address = QFileDialog::getExistingDirectory(this->parentWidget(), tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	edit->setText(address + "/");
	chooseBtnClicked();
}

