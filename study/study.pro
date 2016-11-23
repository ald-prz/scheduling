TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src_generator/configuration.cpp \
    src_generator/exception_input.cpp \
    src_generator/generator.cpp \
    src_generator/generator_abstract.cpp \
    src_generator/output_writer.cpp \
    src_simulator/best_fit_packer.cpp \
    src_simulator/future_event_chain.cpp \
    src_simulator/least_common_multiple.cpp \
    src_simulator/minimum_determiner.cpp \
    src_simulator/processor.cpp \
    src_simulator/simulation_result.cpp \
    src_simulator/simulator_abstract.cpp \
    src_simulator/simulator_global.cpp \
    src_simulator/simulator_partitioned.cpp \
    src_simulator/task_reader.cpp \
    src_study/task.cpp

HEADERS += \
    src_generator/configuration.h \
    src_generator/exception_input.h \
    src_generator/generator.h \
    src_generator/generator_abstract.h \
    src_generator/output_writer.h \
    src_simulator/best_fit_packer.h \
    src_simulator/future_event_chain.h \
    src_simulator/least_common_multiple.h \
    src_simulator/minimum_determiner.h \
    src_simulator/processor.h \
    src_simulator/simulation_result.h \
    src_simulator/simulator_abstract.h \
    src_simulator/simulator_global.h \
    src_simulator/simulator_partitioned.h \
    src_simulator/task_reader.h \
    src_study/task.h \
    src_study/analyzer.h \
    src_study/test_plan.h
