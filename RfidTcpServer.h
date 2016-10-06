#ifndef RFIDTCPSERVER_H
#define RFIDTCPSERVER_H


#include <QObject>
#include <Qdebug>
#include <QTcpServer>
#include <QTcpSocket>


class RfidTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit RfidTcpServer(QObject *parent = 0);
    void startListening();

signals:
    void emitirID(QString id);
public slots:

    void newConnection();
    void disconnected();
    void readyRead();

private:

    QTcpServer *server;

};

#endif // RFIDTCPSERVER_H
