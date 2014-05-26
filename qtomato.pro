#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T11:10:05
#
#-------------------------------------------------

QMAKE_CC  = clang
QMAKE_CXX = clang++

QMAKE_CXXFLAGS += -std=c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtomato
TEMPLATE = app


SOURCES += main.cpp\
        tomato_main.cpp

HEADERS  += tomato_main.h

FORMS    += tomato_main.ui
