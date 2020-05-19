/**
*@mainpage
* This software is used for automatic testing of Windows.\n
* Script can be added, the script is not limited to programming, according to the specified process of communication.\n
* Test reports can be generated automatically.\n
* Designed by BJ CSSV Leon
*/

#include "AC.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AC w;
	w.show();
	return a.exec();
}
