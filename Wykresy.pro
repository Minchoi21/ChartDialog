#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T08:16:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Wykresy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chartwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    chartwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    chartwindow.ui
