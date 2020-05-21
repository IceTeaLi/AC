#pragma once
#include <QDialog>
/**
*  @file     : Server.h 
*  @version  : ver 1.0 
*  @author   : Leon 
*  @date     : 2020/5/19 10:30 
*  @brief    : message server
*/

/**
*@brief get message window
*
* QWidget ,recive WM_COPYDATA message,client communicates with this application by send WM_COPYDATA message to "ipc-server" window.
*/
class Server :
	public QDialog
{
	Q_OBJECT
public:
	Server(QWidget* parent=nullptr);
	~Server() = default;

protected:
	/**
	*@brief The function that receives the message
	*
	* Override function
	*@param QByteArray&: message type[windows_generic_MSG,NSEvent,xcb_generic_event_t]
	*@param void*:message data
	*@param long* unused
	*@return bool: whether return to Qt fot processing
	*/
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
};

