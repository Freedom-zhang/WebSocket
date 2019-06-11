#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T13:28:25
#
#-------------------------------------------------

QT       += gui webchannel widgets websockets core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testHtmltoC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    websocketclientwrapper.h \
    websockettransport.h \
    dialog.h


#idcard start
INCLUDEPATH += $$PWD/3rdparty/idcard/include
LIBS += -L$$PWD/3rdparty/idcard/lib -lcardapi3

IDCARD.files = $$PWD/3rdparty/idcard/bin/*
CONFIG(debug,debug | release){
    IDCARD.path = $$OUT_PWD/debug
}else{
    IDCARD.path = $$OUT_PWD/release
}
#idcard end


CONFIG += mobility
MOBILITY = 

RESOURCES += \
    source.qrc

