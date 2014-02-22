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
    editor/texteditor.cpp \
    application.cpp \
    shared.cpp \
    editor/highlighter.cpp \
    editor/languages/c.cpp \
    editor/languages/css.cpp \
    editor/languages/html.cpp \
    editor/languages/java.cpp \
    editor/languages/latex.cpp \
    editor/languages/python.cpp \
    editor/languages/vala.cpp \
    editor/languages/bash.cpp \
    editor/languages/vb.cpp \
    editor/line_number.cpp \
    treeview.cpp \
    projectslist.cpp

HEADERS  += mainwindow.h \
    plugin_interface.h \
    editor/texteditor.h \
    application.h \
    shared.h \
    editor/highlighter.h \
    ui.h \
    treeview.h \
    projectslist.h

FORMS    +=

RESOURCES += \
    resources.qrc
