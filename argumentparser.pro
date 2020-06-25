# -------------------------------------------------
# Project created by QtCreator 2010-09-15T11:49:05
# -------------------------------------------------
QT -= gui
TARGET = argumentparser
CONFIG += console
CONFIG -= app_bundle
#DEFINES += ARGUMENTPARSER_LIBRARY
TEMPLATE = app
SOURCES += argumentparser.cpp \
    ../argumentresult.cpp \
    argumentresult.cpp \
    argumentdescriptor.cpp \
    test01.cpp
HEADERS += argumentparser.h \
    argumentresult.h \
    argumentdescriptor.h \
    argparse.h
