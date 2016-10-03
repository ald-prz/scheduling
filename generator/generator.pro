CONFIG += c++11

TARGET = generator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    configuration.cpp \
    inputrecognizer.cpp

HEADERS += \
    inputrecognizerabstract.h \
    configuration.h \
    all.h \
    inputrecognizer.h
