#include "NavBar.h"
#include <QDesktopWidget>
#include <QApplication>
NavBar::NavBar(QWidget* parent)
	:QListWidget(parent)
{

	this->setViewportMargins(0, 0, 0, 0);

	hiBtn = new QPushButton(this);
	testBtn = new QPushButton(this);
	resultsBtn = new QPushButton(this);
	settingsBtn = new QPushButton(this);

	hiBtn->setText(QString("Hello"));
	testBtn->setText(QString("Test"));
	resultsBtn->setText(QString("Results"));
	settingsBtn->setText(QString("Settings"));
//	hiBtn->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255))");
	hiBtn->setObjectName("listBtn");
	testBtn->setObjectName("listBtn");
	resultsBtn->setObjectName("listBtn");
	settingsBtn->setObjectName("listBtn");


	buttonGroup = new QButtonGroup(this);
	buttonGroup->addButton(hiBtn);
	buttonGroup->addButton(testBtn);
	buttonGroup->addButton(resultsBtn);
	buttonGroup->addButton(settingsBtn);
	buttonGroup->setId(hiBtn, 0);
	buttonGroup->setId(testBtn, 1);
	buttonGroup->setId(resultsBtn, 2);
	buttonGroup->setId(settingsBtn, 3);

	QListWidgetItem* hiBtnItem = new QListWidgetItem(this);
	QListWidgetItem* testBtnItem = new QListWidgetItem(this);
	QListWidgetItem* resultsBtnItem = new QListWidgetItem(this);
	QListWidgetItem* settingsBtnItem = new QListWidgetItem(this);


	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();

	hiBtnItem->setSizeHint(QSize(this->width(), rect.height() /12));
	testBtnItem->setSizeHint(QSize(this->width(), rect.height() / 12));
	resultsBtnItem->setSizeHint(QSize(this->width(), rect.height() / 12));
	settingsBtnItem->setSizeHint(QSize(this->width(), rect.height() / 12));
	this->setMinimumHeight(rect.height() / 12*5 );

	

	this->addItem(hiBtnItem);
	this->addItem(testBtnItem);
	this->addItem(resultsBtnItem);
	this->addItem(settingsBtnItem);
	this->setItemWidget(hiBtnItem, hiBtn);
	this->setItemWidget(testBtnItem, testBtn);
	this->setItemWidget(resultsBtnItem, resultsBtn);
	this->setItemWidget(settingsBtnItem, settingsBtn);
	

	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));
}

NavBar::~NavBar()
{
}
//@brief		响应按钮点击槽函数
//@details	管理按钮点击后，button group的显示
//@param[in]
void NavBar::buttonClicked(int id)
{
	auto lastBtn = this->buttonGroup->button(lastBtnClickedId);
//	lastBtn->setStyleSheet("{                                 \
 //                        border-style:solid;                     \
   //                      background-color:#3d3d3d;      \
     //                    color:#fff;                                \
       //                  border-radius:7px;                     \
        //                 }");
	auto currentBtn = this->buttonGroup->button(id);
//	currentBtn->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.517, y1:0, x2:0.517, y2:1, stop:0 rgba(29, 29, 29, 255), stop:0.505682 rgba(45, 45, 45, 255), stop:1 rgba(29, 29, 29, 255))");
	lastBtnClickedId = id;
}
