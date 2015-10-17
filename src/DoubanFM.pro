QT       += core gui multimedia network x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DoubanFM
TEMPLATE = app
CONFIG += c++11
LIBS += -lXext -lX11

SOURCES += main.cpp \
    doubanfm.cpp \
    buttonlabel.cpp \
    song.cpp \
    channel.cpp \
    channelframe.cpp \
    lyricframe.cpp \
    logindialog.cpp

HEADERS  += \
    doubanfm.h \
    buttonlabel.h \
    song.h \
    channel.h \
    channelframe.h \
    lyricframe.h \
    constants.h \
    logindialog.h

RESOURCES += \
    resource.qrc

DESTDIR = $$_PRO_FILE_PWD_

Executable.path = /usr/bin
Executable.files = DoubanFM

INSTALLS = Executable

CONFIG(debug, debug|release) {
} else {
    DEFINES += QT_NO_DEBUG_OUTPUT
}
