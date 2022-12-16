#include "beer_racer.h"
#include "./ui_beer_racer.h"

Beer_Racer::Beer_Racer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Beer_Racer)
{
    ui->setupUi(this);

    initKeys();

    //TCP server for modul test
    /*QHostAddress ip;
    ip.setAddress("127.0.0.1");
    server_.listen(ip, 9000);
    connect(&server_, SIGNAL(newConnection()), this, SLOT(onNewCon()));
    tcpSocket_.tcpInit("127.0.0.1", 9000, ui);*/

    tcpSocket_.tcpInit("192.168.1.71", 9000, ui);
    initVideoStream();
}

Beer_Racer::~Beer_Racer()
{
    stream_.stopVideoStream();
    delete ui;
}

void Beer_Racer::on_pushButton_W_pressed(){ qDebug() << "W Button Pressed"; tcpSocket_.tcpWrite("move W"); }

void Beer_Racer::on_pushButton_A_pressed() { qDebug() << "A Button Pressed"; tcpSocket_.tcpWrite("move A"); }

void Beer_Racer::on_pushButton_S_pressed() { qDebug() << "S Button Pressed"; tcpSocket_.tcpWrite("move S"); }

void Beer_Racer::on_pushButton_D_pressed() { qDebug() << "D Button Pressed"; tcpSocket_.tcpWrite("move D"); }

void Beer_Racer::on_pushButton_W_released() { qDebug() << "W Button Released"; tcpSocket_.tcpWrite("stop W"); }

void Beer_Racer::on_pushButton_A_released() { qDebug() << "A Button Released"; tcpSocket_.tcpWrite("stop A"); }

void Beer_Racer::on_pushButton_S_released() { qDebug() << "S Button Released"; tcpSocket_.tcpWrite("stop S"); }

void Beer_Racer::on_pushButton_D_released() { qDebug() << "D Button Released"; tcpSocket_.tcpWrite("stop D"); }

void Beer_Racer::on_pushButton_Shift_pressed()
{
    if(!raceMode_)
    {
        raceMode_ = !raceMode_;
        qDebug() << "raceMode:" << raceMode_;
        tcpSocket_.tcpWrite("raceMode on");
        keys_.setStyle((char)16777248, "background-color:red;");
    }
    else
    {
        raceMode_ = !raceMode_;
        qDebug() << "raceMode:" << raceMode_;
        tcpSocket_.tcpWrite("raceMode off");
        keys_.setStyle((char)16777248, "");
    }
}

void Beer_Racer::initKeys()
{
    keys_.addKey('W', findChild<QPushButton *>("pushButton_W"));
    keys_.addKey('A', findChild<QPushButton *>("pushButton_A"));
    keys_.addKey('S', findChild<QPushButton *>("pushButton_S"));
    keys_.addKey('D', findChild<QPushButton *>("pushButton_D"));
    keys_.addKey((char)16777248, findChild<QPushButton *>("pushButton_Shift"));
}

void Beer_Racer::keyPressEvent( QKeyEvent * event )
{
    keys_.pressEvent(event);
}

void Beer_Racer::keyReleaseEvent( QKeyEvent * event )
{
    keys_.releaseEvent(event);
}

void Beer_Racer::initVideoStream()
{
    ui->streamSettings->setText("rpi-streamer -t 0 --inline -o udp://192.168.1.3:8000 --codec h264 --width 1640 --height 1232");
    stream_.initVideoStream(&tcpSocket_, ui->streamSettings->text().toLatin1());
}

//TCP server function for modul test
/*void Beer_Racer::onNewCon()
{
    serverSocket_ = server_.nextPendingConnection();
    connect(serverSocket_, SIGNAL(readyRead()), this, SLOT(serverRead()));
    serverSocket_->write("beer 9");
}*/

/*void Beer_Racer::serverRead()
{
    auto data = serverSocket_->readAll();
    qDebug() << "Server recived: " << data;
    serverSocket_->write("distance 40");
}*/

void Beer_Racer::on_submitSettings_released()
{
    stream_.changeSettings(ui->streamSettings->text().toLatin1());
}

