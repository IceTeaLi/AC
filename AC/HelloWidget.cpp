#include "HelloWidget.h"
#include "HardwareInfo.h"
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidget>

HelloWidget::HelloWidget(QWidget* parent)
	:QWidget(parent)
{
	main_layout_ = new QVBoxLayout(this);
	this->setLayout(main_layout_);

	title_ = new QLabel(QString(u8"¸ÅÊö"), this);
	hardware_info_list_ = new QTableWidget(6,2,this);
	hardware_info_list_->setShowGrid(false);
	hardware_info_list_->horizontalHeader()->setVisible(false);
	hardware_info_list_->verticalHeader()->setVisible(false);
	hardware_info_list_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	hardware_info_list_->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	main_layout_->addWidget(title_);
	main_layout_->addWidget(hardware_info_list_);

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
	data->insert(QString("CPU"),QString::fromLocal8Bit(info.getCpuInfo().c_str()));
	data->insert(QString("MotherBoard"), QString::fromLocal8Bit(info.getMotherboardInfo().c_str()));

	std::string ram;
	auto ram_list = info.getRAMInfo();
	for (int count = 0; count < ram_list.size(); ++count)
	{
		ram += ram_list[count].c_str();
		if (count != ram_list.size() - 1)
			ram += "\n";	
	}

	data->insert(QString("Memory"), QString::fromLocal8Bit(ram.c_str()));
	data->insert(QString("GPU"), QString::fromLocal8Bit(info.getGPUInfo().c_str()));
	data->insert(QString("OS"), QString::fromLocal8Bit(info.getOSInfo().c_str()));
	
}

void HelloWidget::display_hardware_info(const QMap<QString, QString>& data)
{
	int row = 0;
	QMap<QString, QString>::const_iterator iter;
	for (iter = data.constBegin(); iter != data.constEnd(); ++iter,++row)
	{
		hardware_info_list_->setItem(row, 0, new QTableWidgetItem(iter.key()));
		hardware_info_list_->setItem(row, 1, new QTableWidgetItem(iter.value()));
	}
	hardware_info_list_->show();
	hardware_info_list_->repaint();
}
