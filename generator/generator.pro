CONFIG += c++11

TARGET = generator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    configuration.cpp \
    input_recognizer.cpp \
    exception_input.cpp \
    generator_abstract.cpp \
    task.cpp \
    generator.cpp \
    output_writer.cpp

HEADERS += \
    configuration.h \
    all.h \
    input_recognizer.h \
    input_recognizer_abstract.h \
    exception_input.h \
    generator_abstract.h \
    task.h \
    generator.h \
    output_writer.h
