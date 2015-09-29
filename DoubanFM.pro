QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoubanFM
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp \
    doubanfm.cpp \
    buttonlabel.cpp \
    song.cpp \
    channel.cpp \
    layricframe.cpp \
    channelframe.cpp

HEADERS  += \
    doubanfm.h \
    buttonlabel.h \
    song.h \
    channel.h \
    layricframe.h \
    channelframe.h

RESOURCES += \
    resource.qrc
