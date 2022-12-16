#ifndef BEER_RACER_H
#define BEER_RACER_H

#include <QMainWindow>

#include "Tcp.h"
#include "keys.h"
#include "VideoStream.h"

//TCP server for modultest
//#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class Beer_Racer; }
QT_END_NAMESPACE

class Beer_Racer : public QMainWindow
{
    Q_OBJECT

public:
    Beer_Racer(QWidget *parent = nullptr);
    ~Beer_Racer();

private slots:
    //Button Presses
    void on_pushButton_W_pressed();
    void on_pushButton_A_pressed();
    void on_pushButton_S_pressed();
    void on_pushButton_D_pressed();
    void on_pushButton_W_released();
    void on_pushButton_A_released();
    void on_pushButton_S_released();
    void on_pushButton_D_released();
    void on_pushButton_Shift_pressed();
    void on_submitSettings_released();
    //Func for modultest
    //void onNewCon();
    //void serverRead();
    //Stream Settings

private:
    Ui::Beer_Racer *ui;
    //Keys
    Keys keys_;
    void keyPressEvent( QKeyEvent* event ); //Links keys to pushButtons press
    void keyReleaseEvent( QKeyEvent * event );
    void initKeys();

    //TCP server for modul
    //QTcpServer server_;
    //QTcpSocket* serverSocket_;

    //TCP
    Tcp tcpSocket_;
    //VideoStream
    VideoStream stream_;
    void initVideoStream();
    //Racemode
    bool raceMode_ = 0;
};
#endif // BEER_RACER_H
