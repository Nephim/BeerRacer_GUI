#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QMainWindow>
#include <QProcess>
#include "Tcp.h"

class VideoStream : public QMainWindow
{
    Q_OBJECT
public:
    VideoStream()
    {}

    void initVideoStream(Tcp* tcp, QByteArray settings)
    {
        tcp_ = tcp;
        tcp_->tcpWrite(settings);
        program_ = "C:\\ffmpeg\\bin\\ffplay.exe";
        arguments_ << "udp://192.168.1.71:8000" << "-fflags" << "nobuffer" << "-flags" << "low_delay" << "-framedrop" << "-f" << "h264" << "-framerate" << "40";
        videoStream_.start(program_, arguments_);
    }

    void stopVideoStream()
    {
        tcp_->tcpWrite("rpi-streamer-stop");
        videoStream_.kill();
        videoStream_.waitForFinished();
        qDebug() << "Stream stoped";
    }

    void changeSettings(QByteArray settings)
    {
        stopVideoStream();
        tcp_->tcpWrite(settings);
        videoStream_.start(program_, arguments_);
    }

private:
    QProcess videoStream_;
    Tcp* tcp_;
    QString program_;
    QStringList arguments_;
};

#endif // VIDEOSTREAM_H
