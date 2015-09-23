#-------------------------------------------------
#
# Project created by QtCreator 2014-07-27T14:27:07
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DouBanFM
TEMPLATE = app


SOURCES += main.cpp\
        doubanfm.cpp \
    song.cpp \
    channel.cpp

HEADERS  += doubanfm.h \
    song.h \
    channel.h

FORMS    += doubanfm.ui \
    channel.ui

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -std=c++11
