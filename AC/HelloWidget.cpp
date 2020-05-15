#include "HelloWidget.h"
#include "HardwareInfo.h"
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QHBoxLayout>

HelloWidget::HelloWidget(QWidget* parent)
	:QWidget(parent)
{
	main_layout_ = new QHBoxLayout(this);
	this->setLayout(main_layout_);

	title_ = new QLabel(QString(u8"¸ÅÊö"), this);
	hardware_info_table_ = new QTableWidget(this);

	QMap<QString, QString> data;
	get_hardware_info(&data);
	if(!data.empty())
		display_hardware_info(data);
}

HelloWidget::~HelloWidget()
{
}

void HelloWidget::get_hardware_info(QMap<QString, QString>* data)
{
	auto info = HardwareInfo::getInstance();
	data->insert(QString("CPU"),QString::fromStdString(info.getCpuInfo()));
	data->insert(QString("MB"), QString::fromStdString(info.getMotherboardInfo()));
	for (auto& c : info.getRAMInfo())
	{
		data->insert(QString("RAM"), QString::fromStdString(c));
	}
	data->insert(QString("GPU"), QString::fromStdString(info.getGPUInfo()));
	data->insert(QString("OS"), QString::fromStdString(info.getOSInfo()));
	
}

void HelloWidget::display_hardware_info(const QMap<QString, QString>& data)
{
	int row = 0;
	QMap<QString, QString>::const_iterator iter;
	for (iter = data.constBegin(); iter != data.constEnd(); ++iter,++row)
	{
		hardware_info_table_->setItem(row, 0, &QTableWidgetItem(iter.key()));
		hardware_info_table_->setItem(row, 1, &QTableWidgetItem(iter.value()));
	}
}
