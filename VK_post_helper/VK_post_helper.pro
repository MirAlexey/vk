#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T16:47:09
#
#-------------------------------------------------

QT       += core gui sql webkit webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VK_post_helper
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    tag.cpp \
    group.cpp \
    account.cpp \
    element_bd.cpp \
    conector.cpp \
    bdmanager.cpp \
    post.cpp \
    listmanager.cpp \
    fabrika_tg_gr_ac.cpp \
    qlineeditfortag.cpp \
    checkboxtagforgroup.cpp \
    vkmanager.cpp \
    json.cpp \
    myitemmodel.cpp \
    mymodel2.cpp \
    myproxymodel.cpp \
    myfiltermodel.cpp

HEADERS  += widget.h \
    tag.h \
    group.h \
    account.h \
    element_bd.h \
    conector.h \
    bdmanager.h \
    post.h \
    listmanager.h \
    fabrika_tg_gr_ac.h \
    qlineeditfortag.h \
    checkboxtagforgroup.h \
    vkmanager.h \
    json.h \
    myitemmodel.h \
    listitems.h \
    mymodel2.h \
    myproxymodel.h \
    myfiltermodel.h

FORMS    += widget.ui
