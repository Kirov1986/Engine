#-------------------------------------------------
#
# Project created by QtCreator 2015-02-16T19:26:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Engine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    character.cpp \
    texture.cpp \
    basetexturemodule.cpp \
    effect.cpp \
    structure.cpp \
    functions.cpp \
    projectile.cpp \
    button.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    character.h \
    texture.h \
    basetexturemodule.h \
    effect.h \
    structure.h \
    functions.h \
    projectile.h \
    button.h \
    form.h

FORMS    += mainwindow.ui
