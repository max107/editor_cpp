#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T16:06:17
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    texteditor.cpp \
    application.cpp \
    shared.cpp \
    highlighter.cpp \
    languages/c.cpp \
    languages/css.cpp \
    languages/html.cpp \
    languages/java.cpp \
    languages/latex.cpp \
    languages/python.cpp \
    languages/vala.cpp \
    languages/bash.cpp \
    languages/vb.cpp \
    line_number.cpp

HEADERS  += mainwindow.h \
    plugin_interface.h \
    texteditor.h \
    application.h \
    shared.h \
    highlighter.h \
    ui.h

FORMS    +=

RESOURCES += \
    resources.qrc
