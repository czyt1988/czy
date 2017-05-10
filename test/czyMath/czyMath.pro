TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
include(../../czy.pri)
#include(deployment.pri)
#qtcAddDeployment()

