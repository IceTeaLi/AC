/**
*@mainpage
* This software is used for automatic testing of Windows.\n
* Script can be added, the script is not limited to programming, according to the specified process of communication.\n
* Test reports can be generated automatically.\n
* Designed by BJ CSSV Leon
* @image html hello.png
*/
#include "AC.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AC w;

	{
		QDesktopWidget* desktopWidget = QApplication::desktop();
		QRect rect = desktopWidget->screenGeometry();
		w.resize(QSize(rect.width() / 2, rect.height() / 2));
	}

	w.show();
	return a.exec();
}
