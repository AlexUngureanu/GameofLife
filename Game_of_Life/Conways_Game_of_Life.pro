#-------------------------------------------------
#
# Project created by QtCreator 2016-04-24T03:39:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Conways_Game_of_Life
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ../Conway_Game_of_Life/Cell.cpp \
    ../Conway_Game_of_Life/GoL_Controller.cpp \
    ../Conway_Game_of_Life/Node.cpp \
    ../Conway_Game_of_Life/Point.cpp \
    ../Conway_Game_of_Life/WorldState.cpp \
    ../Conway_Game_of_Life/Cell_Dynamic_Array.cpp

HEADERS  += widget.h \
    ../Conway_Game_of_Life/Cell.h \
    ../Conway_Game_of_Life/GoL_Controller.h \
    ../Conway_Game_of_Life/Node.h \
    ../Conway_Game_of_Life/Point.h \
    ../Conway_Game_of_Life/WorldState.h \
    ../Conway_Game_of_Life/Cell_Dynamic_Array.h

FORMS    += widget.ui
