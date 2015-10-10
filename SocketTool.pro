#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T17:18:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = SocketTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    multicastwidget.cpp \
    udpsocketwidget.cpp \
    updsocketoperatewidget.cpp \
    tcpserverwidget.cpp \
    tcpserveroperatewidget.cpp \
    tcpsocketwidget.cpp \
    tcpsocketoperatewidget.cpp

HEADERS  += mainwindow.h \
    multicastwidget.h \
    stdafx.h \
    udpsocketwidget.h \
    updsocketoperatewidget.h \
    tcpserverwidget.h \
    tcpserveroperatewidget.h \
    tcpsocketwidget.h \
    tcpsocketoperatewidget.h

FORMS    += mainwindow.ui \
    multicastwidget.ui \
    udpsocketwidget.ui \
    updsocketoperatewidget.ui \
    tcpserverwidget.ui \
    tcpserveroperatewidget.ui \
    tcpsocketwidget.ui \
    tcpsocketoperatewidget.ui
