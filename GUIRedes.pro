#-------------------------------------------------
#
# Project created by QtCreator 2016-10-05T19:35:18
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUIRedes
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Banco.cpp \
    RfidTcpServer.cpp

HEADERS  += MainWindow.h \
    Banco.h \
    RfidTcpServer.h

FORMS    += MainWindow.ui
