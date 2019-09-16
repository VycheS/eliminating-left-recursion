TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    grammar.cpp \
    symbol.cpp

HEADERS += \
    grammar.h \
    symbol.h
