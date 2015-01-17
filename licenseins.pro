#-------------------------------------------------
#
# Project created by QtCreator 2015-01-03T17:01:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = licenseins
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    CmdParameter.cpp \
    CmdParser.cpp \
    LicenseImp.cpp \
    LicenseInsImp.cpp \
    LicenseDelImp.cpp \
    LicenseChangeImp.cpp

HEADERS += \
    CmdParameter.h \
    CmdParser.h \
    Exception.h \
    LicenseImp.h \
    LicenseInsImp.h \
    LicenseDelImp.h \
    LicenseChangeImp.h
