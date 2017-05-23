#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T16:58:58
#
#-------------------------------------------------

QT       -= gui

TARGET = bioblocksExecution
TEMPLATE = lib

DEFINES += BIOBLOCKSEXECUTION_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    bioblocksExecution/bioblocksexecution.h \
    bioblocksExecution/bioblocksexecution_global.h \
    bioblocksExecution/bioblocksSimulation/bioblocksrunningsimulator.h

SOURCES += \
    bioblocksExecution/bioblocksexecution.cpp \
    bioblocksExecution/bioblocksSimulation/bioblocksrunningsimulator.cpp

debug {
    QMAKE_POST_LINK=X:\bioblocksExecution\bioblocksExecution\setDLL.bat $$shell_path($$OUT_PWD/debug) debug

    INCLUDEPATH += X:\utils\dll_debug\include
    LIBS += -L$$quote(X:\utils\dll_debug\bin) -lutils

    INCLUDEPATH += X:\protocolGraph\dll_debug\include
    LIBS += -L$$quote(X:\protocolGraph\dll_debug\bin) -lprotocolGraph

    INCLUDEPATH += X:\bioblocksTranslation\dll_debug\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_debug\bin) -lbioblocksTranslation

    INCLUDEPATH += X:\fluidicMachineModel\dll_debug\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_debug\bin) -lFluidicMachineModel

    INCLUDEPATH += X:\commomModel\dll_debug\include
    LIBS += -L$$quote(X:\commomModel\dll_debug\bin) -lcommonModel
}

!debug {
    QMAKE_POST_LINK=X:\bioblocksExecution\bioblocksExecution\setDLL.bat $$shell_path($$OUT_PWD/release) release

    INCLUDEPATH += X:\utils\dll_release\include
    LIBS += -L$$quote(X:\utils\dll_release\bin) -lutils

    INCLUDEPATH += X:\protocolGraph\dll_release\include
    LIBS += -L$$quote(X:\protocolGraph\dll_release\bin) -lprotocolGraph

    INCLUDEPATH += X:\bioblocksTranslation\dll_release\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_release\bin) -lbioblocksTranslation

    INCLUDEPATH += X:\bioblocksTranslation\dll_release\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_release\bin) -lbioblocksTranslation

    INCLUDEPATH += X:\commomModel\dll_release\include
    LIBS += -L$$quote(X:\commomModel\dll_release\bin) -lcommonModel
}

INCLUDEPATH += X:\libraries\json-2.1.1\src
INCLUDEPATH += X:\libraries\boost_1_63_0
INCLUDEPATH += X:\libraries\cereal-1.2.2\include
