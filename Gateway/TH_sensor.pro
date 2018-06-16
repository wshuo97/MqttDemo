#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T15:59:22
#
#-------------------------------------------------

QT       += core gui network

TARGET = TH_sensor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    temp_humi_ligh.cpp \
    serialservice.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp \
    mythread.cpp \
    enddevice.cpp

HEADERS  += mainwindow.h \
    temp_humi_ligh.h \
    serialservice.h \
    qextserialbase.h \
    posix_qextserialport.h \
    mythread.h \
    enddevice.h

FORMS    += mainwindow.ui
