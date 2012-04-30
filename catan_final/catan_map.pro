#-------------------------------------------------
#
# Project created by QtCreator 2012-04-08T12:26:30
#
#-------------------------------------------------

QT       += core gui

TARGET = catan_map
TEMPLATE = app


SOURCES += main.cpp\
        catan_map.cpp \
    map_tracker/map_tracker.cpp \
    player/Player.cpp \
    player/Node.cpp

HEADERS  += catan_map.h \
    map_tracker/map_tracker.h \
    player/Player.h \
    player/Node.h

FORMS    += catan_map.ui
