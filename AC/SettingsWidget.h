#pragma once

#include <qwidget.h>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFile>
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>


			//@brief							修改全局skin
			//@param[in]					qstring->QSS文件路径
			//@attention
static void changeSkin(const QString& filename)
{

	QString qss;
	QFile qssFile(filename);
	qssFile.open(QFile::ReadOnly);

	if (qssFile.isOpen())
	{
		qss = QLatin1String(qssFile.readAll());
		qApp->setStyleSheet(qss);
		qssFile.close();
	}
}
class Skins :
	public QHBoxLayout
{
	Q_OBJECT
public:
	Skins(QWidget* parent = nullptr);
	~Skins();

private:
	QPushButton* chooseBtn;
	QLabel* label;
	QComboBox* combox;

	void refresh();
	void scanQSSFile(const QString& folder, QStringList& list);

private slots:
	void chooseBtnClicked();

public slots:
	void getSkinsFolderChanged() { refresh(); }
};

class FolderSetting :
	public QHBoxLayout
{
	Q_OBJECT
public:
	FolderSetting(const QString& value, const QString& label, QWidget* parent = nullptr);
	~FolderSetting();

private:
	QLabel* label;
	QString address;
	QString settingConfigValue;

	QLineEdit* edit;
	QPushButton* searchFolderBtn;
	QPushButton* chooseBtn;

private slots:
	void chooseBtnClicked();
	void searchFolderBtnClicked();

signals:
	void emitSkinsFolderChanged();
};


class SettingsWidget :
	public QWidget
{
	Q_OBJECT
public:
	SettingsWidget(QWidget* parent = nullptr);
	~SettingsWidget();

private:
	Skins* skinsLayout;
	FolderSetting* scriptsFolderLayout;
	FolderSetting* resultsFolderLayout;
	FolderSetting* skinsFolderLayout;
	QGridLayout* mainLayout;
};
