#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T19:13:02
#
#-------------------------------------------------
QT       += widgets core qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuffProject
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    hufftree.cpp \
    compress.cpp \
    decompress.cpp \
    actionhuffman.cpp

HEADERS += \
    hufftree.h \
    node.h \
    compress.h \
    decompress.h \
    actionhuffman.h

FORMS    +=
RC_FILE +=dialogo.rc

RESOURCES += \
    qml.qrc
