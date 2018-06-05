# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = z6_gnuplot_robot_przeszkody

QT = core gui

QMAKE_CXXFLAGS += -pedantic

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS = \
   $$PWD/inc/lacze_do_gnuplota.hh \
   $$PWD/inc/ObiektGraficzny.hh \
   $$PWD/inc/Path.hh \
   $$PWD/inc/Robot.hh \
   $$PWD/inc/rozmiar.h \
   $$PWD/inc/Scene.hh \
   $$PWD/inc/SWektor.hh \
   $$PWD/inc/Vertices.hh \
   $$PWD/inc/Wektor3D.hh \
   $$PWD/emitter.h \
   $$PWD/okno.h \
    obstacle.h \
    gjk_collision_detection.h \
    create.h \
    objectfactory.h

SOURCES = \
   $$PWD/src/lacze_do_gnuplota.cpp \
   $$PWD/src/main.cpp \
   $$PWD/src/ObiektGraficzny.cpp \
   $$PWD/src/Path.cpp \
   $$PWD/src/Robot.cpp \
   $$PWD/src/Scene.cpp \
   $$PWD/src/Vertices.cpp \
   $$PWD/emitter.cpp \
   $$PWD/okno.cpp \
    obstacle.cpp \
    gjk_collision_detection.cpp \
    create.cpp \
    objectfactory.cpp

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/inc

#DEFINES = 

