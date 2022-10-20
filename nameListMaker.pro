QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    armynamelist.cpp \
    characternamelist.cpp \
    fleetnamelist.cpp \
    loaddatafiles.cpp \
    localkeylist.cpp \
    main.cpp \
    mainwindow.cpp \
    planetnamelist.cpp \
    shipnamelist.cpp

HEADERS += \
    armynamelist.h \
    characternamelist.h \
    fleetnamelist.h \
    helperFunctions.h \
    loaddatafiles.h \
    localkeylist.h \
    mainwindow.h \
    planetnamelist.h \
    shipnamelist.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target