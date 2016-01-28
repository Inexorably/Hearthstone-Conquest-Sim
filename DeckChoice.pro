#-------------------------------------------------
#
# Project created by QtCreator 2015-12-31T11:59:36
#
#-------------------------------------------------

QT       += core gui
RC_FILE = resources.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeckChoice
TEMPLATE = app

ICON = sim.icns

RC_FILE = DeckChoice.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    globals.cpp \
    structures.cpp \
    sim.cpp \
    simthread.cpp

HEADERS  += mainwindow.h \
    globals.h \
    structures.h \
    sim.h \
    simthread.h \
    version.h

FORMS    += mainwindow.ui
