#-------------------------------------------------
#
# Project created by QtCreator 2020-06-14T07:28:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qLaserEngraver
TEMPLATE = app
DEFINES = "VERSION=1" "MKBITMAP=1"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    laserImage.cpp \
    pottrace/trans.c \
    pottrace/trace.c \
    pottrace/render.c \
    pottrace/progress_bar.c \
    pottrace/potracelib.c \
    pottrace/mkbitmap.c \
    pottrace/lzw.c \
    pottrace/greymap.c \
    pottrace/getopt1.c \
    pottrace/getopt.c \
    pottrace/flate.c \
    pottrace/decompose.c \
    pottrace/curve.c \
    pottrace/bitmap_io.c \
    pottrace/bbox.c \
    pottrace/backend_xfig.c \
    pottrace/backend_svg.c \
    pottrace/backend_pgm.c \
    pottrace/backend_pdf.c \
    pottrace/backend_geojson.c \
    pottrace/backend_eps.c \
    pottrace/backend_dxf.c \
    pottrace/pottrace.c

HEADERS += \
        mainwindow.h \
    laserImage.h \
    pottrace/trans.h \
    pottrace/trace.h \
    pottrace/render.h \
    pottrace/progress_bar.h \
    pottrace/progress.h \
    pottrace/potracelib.h \
    pottrace/platform.h \
    pottrace/lzw.h \
    pottrace/lists.h \
    pottrace/greymap.h \
    pottrace/flate.h \
    pottrace/decompose.h \
    pottrace/curve.h \
    pottrace/bitops.h \
    pottrace/bitmap_io.h \
    pottrace/bitmap.h \
    pottrace/bbox.h \
    pottrace/backend_xfig.h \
    pottrace/backend_svg.h \
    pottrace/backend_pgm.h \
    pottrace/backend_pdf.h \
    pottrace/backend_geojson.h \
    pottrace/backend_eps.h \
    pottrace/backend_dxf.h \
    pottrace/auxiliary.h \
    pottrace/pottrace.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
