#pragma once
#include <QListWidget>


class NavBar :public QListWidget
{
	Q_OBJECT
public:
	NavBar(QWidget* parent = nullptr)
		:QListWidget(parent)
	{

	}

protected:
	virtual void resizeEvent(QResizeEvent* event)override
	{
		for (int row = 0; row < this->count(); ++row)
		{
			this->item(row)->setSizeHint(QSize(this->item(row)->sizeHint().width(), this->parentWidget()->height() / 8));
		}
	}
};