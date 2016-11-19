TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    task.cpp \
    future_event_chain.cpp \
    least_common_multiple.cpp \
    simulator_abstract.cpp \
    simulator_global.cpp \
    processor.cpp \
    task_reader.cpp \
    simulation_result.cpp \
    simulator_partitioned.cpp

HEADERS += \
    task.h \
    simulator_abstract.h \
    simulator_global.h \
    future_event_chain.h \
    least_common_multiple.h \
    processor.h \
    task_reader.h \
    simulation_result.h \
    best_fit_packer.h \
    simulator_partitioned.h
