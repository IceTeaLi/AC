#pragma once
/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2020, Leon 
    *  @All rights reserved 
 
    *  @file     : NavBar.h 
    *  @version  : ver 1.0 
 
    *  @author   : Leon 
    *  @date     : 2020/4/22 16:41 
    *  @brief    : brief 
*****************************************************************************/

#include <QListWidget>
#include <QButtonGroup>
#include <QPushButton>

//@brief                    ������
//@details                  �ṩHi��Test��Result��Settings���ڵĵ���
class NavBar :
    public QListWidget
{
    Q_OBJECT
public:
    NavBar(QWidget* parent = nullptr);
    ~NavBar();

private:
    QButtonGroup* buttonGroup;

    QPushButton* hiBtn;
    QPushButton* testBtn;
    QPushButton* resultsBtn;
    QPushButton* settingsBtn;

    int lastBtnClickedId = 0;
private slots:
    void buttonClicked(int id);
};

