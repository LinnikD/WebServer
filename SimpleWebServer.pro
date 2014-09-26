TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -pthread

SOURCES += main.cpp \
    request.cpp \
    filesystem.cpp \
    response.cpp \
    httpserver.cpp \
    decoder.cpp \
    clientsqueue.cpp \
    worker.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    request.h \
    filesystem.h \
    response.h \
    httpserver.h \
    decoder.h \
    clientsqueue.h \
    worker.h

