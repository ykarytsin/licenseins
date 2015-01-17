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


SOURCES += \
    sources/CmdParameter.cpp \
    sources/CmdParser.cpp \
    sources/LicenseChangeImp.cpp \
    sources/LicenseDelImp.cpp \
    sources/LicenseImp.cpp \
    sources/LicenseInsImp.cpp \
    sources/main.cpp

HEADERS += \
    sources/CmdParameter.h \
    sources/CmdParser.h \
    sources/Exception.h \
    sources/LicenseChangeImp.h \
    sources/LicenseDelImp.h \
    sources/LicenseImp.h \
    sources/LicenseInsImp.h
