#-------------------------------------------------
#
# Project created by QtCreator 2021-07-21T15:41:12
#
#-------------------------------------------------

QT       += core gui

QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kursishi2
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    admin.cpp \
    user.cpp

HEADERS  += login.h \
    admin.h \
    user.h

FORMS    += login.ui \
    admin.ui \
    user.ui

RESOURCES += \
    images.qrc
