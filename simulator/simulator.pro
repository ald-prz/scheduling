TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    task.cpp

HEADERS += \
    task.h \
    task_loader.h \
    simulator_abstract.h \
    simulator_global.h \
    future_event_chain.h \
    least_common_multiple.h \
    processor.h
