#ifndef TCP_H
#define TCP_H

#include <QMainWindow>
//#include <QByteArray>
#include <QString>
#include <QTcpSocket>
#include "./ui_beer_racer.h"

class Tcp : public QMainWindow
{
    Q_OBJECT
public:
    Tcp()
    {
        connect(&tcpSocket_, SIGNAL(readyRead()), this, SLOT(tcpRead()));   //Connect readyRead signal to the tcpRead function
    }

    void tcpInit(const QString& ip, quint16 port, Ui::Beer_Racer* ui)
    {
        ui_ = ui;
        ip_.setAddress(ip);
        port_ = port;
        tcpSocket_.connectToHost(ip_, port_);
    }

    void tcpWrite(QByteArray data)
    {
        tcpSocket_.write(data, qstrlen(data));
        tcpSocket_.waitForBytesWritten();
    }

public slots:
    void tcpRead()
    {
        QString data = tcpSocket_.readAll();                    //Read received data
        QString prefix = data.section(' ', 0, 0);               //Take the first word/substring
        QString sufix = data.section(' ', 1, 1);
        if(prefix == "beer")                                    //If prefix beer
        {
            ui_->numOfBeer->setText(data.section(' ', 1, 1));   //Update ui beer label
        }
        else if(prefix == "distance")                           //If prefix distance
        {
            ui_->numDistance->setText(data.section(' ', 1, 1)); //Update ui distance label
        }
        else
        {
            qDebug() << "Unknown/Error ";
        }
        qDebug() << "Client recived" << prefix << sufix << "\n";
    }

private:
    Ui::Beer_Racer* ui_;        //Pointer to ui used to update labels
    QTcpSocket tcpSocket_;      //QTcpSocket used to communicate with TcpServer on Rpi
    QHostAddress ip_;           //TcpServer Address
    quint16 port_;              //TcpServer Port
};

#endif // TCP_H

