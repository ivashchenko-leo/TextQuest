#-------------------------------------------------
#
# Project created by QtCreator 2013-10-04T21:23:14
#
#-------------------------------------------------

QT       += core gui \
        xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextQuest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    settings.cpp \
    gamemenu.cpp \
    #xmlchapters.cpp \
    chaptersdialog.cpp \
    xmldom.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    settings.h \
    gamemenu.h \
    #xmlchapters.h \
    chaptersdialog.h \
    xmldom.h

FORMS    += mainwindow.ui \
    settings.ui \
    gamemenu.ui \
    chaptersdialog.ui
