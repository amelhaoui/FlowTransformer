#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T17:35:56
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlowTransformer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp \
    emc_parser.cpp \
    emc_parser_utility.cpp \
    tablemodel.cpp \
    itemtabledelegate.cpp \
    treemodelcompleter.cpp \
    inc/tinyxml2.cpp \
    dragdropmodel.cpp

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h \
    emc_parse_utility.h \
    tablemodel.h \
    itemtabledelegate.h \
    treemodelcompleter.h \
    inc/tinyxml2.h \
    dragdropmodel.h \


FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/inc/release/ -lexpat.1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/inc/debug/ -lexpat.1
else:unix: LIBS += -L$$PWD/inc/ -lexpat.1

INCLUDEPATH += $$PWD/inc
DEPENDPATH += $$PWD/inc
