#
# tspress project file
#

greaterThan(QT_MAJOR_VERSION, 4): cache

TEMPLATE = app

TARGET = tspress

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += release

target.path = /usr/bin
INSTALLS += target

INCLUDEPATH += GeneratedFiles

MOC_DIR = GeneratedFiles
OBJECTS_DIR = Objects
UI_DIR = GeneratedFiles
RCC_DIR = GeneratedFiles

SOURCES += main.cpp \
           tspress.cpp

HEADERS += tspress.h

