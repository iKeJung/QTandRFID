#include "RfidTcpServer.h"

RfidTcpServer::RfidTcpServer(QObject *parent) : QObject(parent)
{
    startListening();
}

void RfidTcpServer::startListening()
{
    server = new QTcpServer(this);

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(!server->listen(QHostAddress::AnyIPv4, 2222))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void RfidTcpServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socket->write("Waiting for data\r\n");
    socket->flush();
    connect(socket,SIGNAL(readyRead()),SLOT(readyRead()));
    connect(socket,SIGNAL(disconnected()), SLOT(disconnected()));
    qDebug() << "Connection coming from " << socket->peerAddress().toString();



    // PEGAR DADOS
    // VERIFICAR
    // CONVERSAR COM DB SQL
    // MANDAR CONFIRMACAO

    //socket->close();
}

void RfidTcpServer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

void RfidTcpServer::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    while(socket->bytesAvailable() > 0){
        QString id =  socket->readAll();
        qDebug() << id;
        emit emitirID(id);
    }
    socket->write("Henrique\r\n");
    socket->flush();
}
