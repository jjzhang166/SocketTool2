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
    socketoperatewidget.cpp \
    clientwidget.cpp \
    udpsocketwidget.cpp \
    updsocketoperatewidget.cpp

HEADERS  += mainwindow.h \
    multicastwidget.h \
    stdafx.h \
    socketoperatewidget.h \
    clientwidget.h \
    udpsocketwidget.h \
    updsocketoperatewidget.h

FORMS    += mainwindow.ui \
    multicastwidget.ui \
    socketoperatewidget.ui \
    clientwidget.ui \
    udpsocketwidget.ui \
    updsocketoperatewidget.ui
