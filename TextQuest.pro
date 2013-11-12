#-------------------------------------------------
#
# Project created by QtCreator 2013-10-04T21:23:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextQuest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    settings.cpp \
    gamemenu.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    settings.h \
    gamemenu.h

FORMS    += mainwindow.ui \
    settings.ui \
    gamemenu.ui
