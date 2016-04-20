QT += core
QT -= gui

CONFIG += c++11

TARGET = Game_of_Life
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Node.cpp \
    Point.cpp \
    Cell.cpp \
    WorldState.cpp \
    GoL_Controller.cpp \
    GoL_Viewer.cpp

HEADERS += \
    Node.h \
    Point.h \
    Cell.h \
    WorldState.h \
    GoL_Controller.h \
    GoL_Viewer.h
