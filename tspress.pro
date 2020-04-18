#
# tspress project file
#

cache

TEMPLATE = app

TARGET = tspress

QT += core gui widgets

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

