#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T18:00:22
#
#-------------------------------------------------

QT       += core gui sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerMultiThread
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    register.cpp \
        widget.cpp \
    myserver.cpp \
    mysocket.cpp \
    mythread.cpp

HEADERS  += widget.h \
    login.h \
    myserver.h \
    mysocket.h \
    mythread.h \
    debugonoroff.h \
    protocolcommand.h \
    register.h

FORMS    += widget.ui

RESOURCES += \
    documents.qrc
