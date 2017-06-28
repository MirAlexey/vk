#-------------------------------------------------
#
# Project created by QtCreator 2015-07-02T22:09:57
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VKvideohelper
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    castomvkwebview.cpp \
    interceptoraccessmanager.cpp \
    vkmanager.cpp \
    json.cpp \
    videofile.cpp \
    account.cpp

HEADERS  += widget.h \
    castomvkwebview.h \
    interceptoraccessmanager.h \
    vkmanager.h \
    json.h \
    videofile.h \
    account.h

FORMS    += widget.ui
