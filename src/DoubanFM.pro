QT       += core gui widgets multimedia network x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += 

TARGET = DoubanFM
TEMPLATE = app
CONFIG += c++11
LIBS += -lXext -lX11

SOURCES += main.cpp \
    doubanfm.cpp \
    buttonlabel.cpp \
    song.cpp \
    lyricframe.cpp \
    logindialog.cpp \
    user.cpp \
    channel/channel.cpp \
    channel/channelframe.cpp \
    channel/channelmodel.cpp

HEADERS  += \
    doubanfm.h \
    buttonlabel.h \
    song.h \
    lyricframe.h \
    constants.h \
    logindialog.h \
    user.h \
    channel/channel.h \
    channel/channelframe.h \
    channel/channelmodel.h

RESOURCES += \
    resource.qrc

DESTDIR = $$_PRO_FILE_PWD_

Executable.path = $$INSTROOT/usr/bin
icon.path = $$INSTROOT/usr/share/icons/hicolor/256x256/apps
desktop.path = $$INSTROOT/usr/share/applications
Executable.files = DoubanFM
icon.files = resource/images/doubanFM.png
desktop.files = ../DoubanFM.desktop
INSTALLS = Executable icon desktop

CONFIG(debug, debug|release) {
} else {
    DEFINES += QT_NO_DEBUG_OUTPUT
}
