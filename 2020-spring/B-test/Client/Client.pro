#-------------------------------------------------
#
# Project created by QtCreator 2018-08-01T11:57:10
#
#-------------------------------------------------

QT       += core gui sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
        register.cpp \
        widget.cpp

HEADERS  += widget.h \
    debugonoroff.h \
    login.h \
    protocolcommand.h \
    register.h

FORMS    += widget.ui

RESOURCES += \
    document.qrc
