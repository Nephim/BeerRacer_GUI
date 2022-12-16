#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QProcess>
#include <QMainWindow>

class WorkerThread : public QThread
{
    Q_OBJECT
    void run() override {
        QString result;

        /* ... here is the expensive or blocking operation ... */

        /*QProcess* ffplay_ = new QProcess;
        QString program_ = "C:\\ffmpeg\\bin\\ffplay.exe";
        QStringList arguments_;
        arguments_ << "udp://192.168.1.71:8000" << "-fflags" << "nobuffer" << "-flags" << "low_delay" << "-framedrop" << "-f" << "mjpeg" << "-framerate" << "40";
        //arguments_ << "tcp://192.168.1.71:8000" << "-fflags" << "nobuffer" << "-flags" << "low_delay" << "-framedrop" << "-f" << "h264" << "-framerate" << "30";
        ffplay_->start(program_, arguments_);*/

        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);
};

/*void WorkerThread::startWorkInAThread()
{
    WorkerThread *workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}*/

#endif // WORKERTHREAD_H
