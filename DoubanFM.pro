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
    channelframe.cpp \
    lyricframe.cpp

HEADERS  += \
    doubanfm.h \
    buttonlabel.h \
    song.h \
    channel.h \
    channelframe.h \
    lyricframe.h

RESOURCES += \
    resource.qrc
