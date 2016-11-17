TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    task.cpp \
    task_reader.cpp \
    future_event_chain.cpp \
    least_common_multiple.cpp \
    processor.cpp \
    simulator_abstract.cpp \
    simulator_global.cpp

HEADERS += \
    task.h \
    simulator_abstract.h \
    simulator_global.h \
    future_event_chain.h \
    least_common_multiple.h \
    processor.h \
    task_reader.h
