#-------------------------------------------------
#
# Project created by QtCreator 2013-02-28T11:11:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = yolo-chat
TEMPLATE = app


SOURCES += main.cpp\
        chatwindow.cpp \
    client/client_net.cpp \
    server/server_net.cpp \
    clientsettingsdialog.cpp \
    serversettingsdialog.cpp

HEADERS  += chatwindow.h \
    client/client_net.h \
    server/server_net.h \
    utils.h \
    clientsettingsdialog.h \
    serversettingsdialog.h

FORMS    += chatwindow.ui \
    clientsettingsdialog.ui \
    serversettingsdialog.ui
