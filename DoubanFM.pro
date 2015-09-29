#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T21:36:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia network

TARGET = DoubanFM
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp \
    doubanfm.cpp \
    buttonlabel.cpp \
    song.cpp \
    channel.cpp \
    layricframe.cpp

HEADERS  += \
    doubanfm.h \
    buttonlabel.h \
    song.h \
    channel.h \
    layricframe.h

RESOURCES += \
    resource.qrc
