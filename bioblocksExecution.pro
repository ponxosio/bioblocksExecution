#-------------------------------------------------
#
# Project created by QtCreator 2017-05-23T16:58:58
#
#-------------------------------------------------

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}
    # ensure one "debug" or "release" in CONFIG so they can be used as
    #   conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

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
    bioblocksExecution/bioblocksSimulation/bioblocksrunningsimulator.h \
    bioblocksExecution/protocolexecution/generalmodelexecutor.h \
    bioblocksExecution/usercommunications/usercommunicationinterface.h \
    bioblocksExecution/protocolexecution/bioblocksprotocolexecutor.h \
    bioblocksExecution/usercommunications/consoleusercommunications.h \
    bioblocksExecution/protocolexecution/customsleepmsthread.h

SOURCES += \
    bioblocksExecution/bioblocksexecution.cpp \
    bioblocksExecution/bioblocksSimulation/bioblocksrunningsimulator.cpp \
    bioblocksExecution/protocolexecution/generalmodelexecutor.cpp \
    bioblocksExecution/protocolexecution/bioblocksprotocolexecutor.cpp \
    bioblocksExecution/usercommunications/consoleusercommunications.cpp \
    bioblocksExecution/protocolexecution/customsleepmsthread.cpp

debug {
    QMAKE_POST_LINK=X:\bioblocksExecution\bioblocksExecution\setDLL.bat $$shell_path($$OUT_PWD/debug) debug

    INCLUDEPATH += X:\fluidicMachineModel\dll_debug\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_debug\bin) -lFluidicMachineModel

    INCLUDEPATH += X:\constraintsEngine\dll_debug\include
    LIBS += -L$$quote(X:\constraintsEngine\dll_debug\bin) -lconstraintsEngineLibrary

    INCLUDEPATH += X:\utils\dll_debug\include
    LIBS += -L$$quote(X:\utils\dll_debug\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_debug\include
    LIBS += -L$$quote(X:\commomModel\dll_debug\bin) -lcommonModel

    INCLUDEPATH += X:\protocolGraph\dll_debug\include
    LIBS += -L$$quote(X:\protocolGraph\dll_debug\bin) -lprotocolGraph

    INCLUDEPATH += X:\blockly_fluidicMachine_translator\dll_debug\include
    LIBS += -L$$quote(X:\blockly_fluidicMachine_translator\dll_debug\bin) -lblocklyFluidicMachineTranslator

    INCLUDEPATH += X:\fluidicModelMapping\dll_debug\include
    LIBS += -L$$quote(X:\fluidicModelMapping\dll_debug\bin) -lFluidicModelMapping

    INCLUDEPATH += X:\bioblocksTranslation\dll_debug\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_debug\bin) -lbioblocksTranslation
}

!debug {
    QMAKE_POST_LINK=X:\bioblocksExecution\bioblocksExecution\setDLL.bat $$shell_path($$OUT_PWD/release) release

    INCLUDEPATH += X:\fluidicMachineModel\dll_release\include
    LIBS += -L$$quote(X:\fluidicMachineModel\dll_release\bin) -lFluidicMachineModel

    INCLUDEPATH +=X:\constraintsEngine\dll_release\include
    LIBS += -L$$quote(X:\constraintsEngine\dll_release\bin) -lconstraintsEngineLibrary

    INCLUDEPATH += X:\utils\dll_release\include
    LIBS += -L$$quote(X:\utils\dll_release\bin) -lutils

    INCLUDEPATH += X:\commomModel\dll_release\include
    LIBS += -L$$quote(X:\commomModel\dll_release\bin) -lcommonModel

    INCLUDEPATH += X:\protocolGraph\dll_release\include
    LIBS += -L$$quote(X:\protocolGraph\dll_release\bin) -lprotocolGraph

    INCLUDEPATH += X:\blockly_fluidicMachine_translator\dll_release\include
    LIBS += -L$$quote(X:\blockly_fluidicMachine_translator\dll_release\bin) -lblocklyFluidicMachineTranslator

    INCLUDEPATH += X:\fluidicModelMapping\dll_release\include
    LIBS += -L$$quote(X:\fluidicModelMapping\dll_release\bin) -lFluidicModelMapping

    INCLUDEPATH += X:\bioblocksTranslation\dll_release\include
    LIBS += -L$$quote(X:\bioblocksTranslation\dll_release\bin) -lbioblocksTranslation
}

INCLUDEPATH += X:\libraries\json-2.1.1\src
INCLUDEPATH += X:\libraries\boost_1_63_0
INCLUDEPATH += X:\libraries\cereal-1.2.2\include

INCLUDEPATH += X:\swipl\include
LIBS += -L$$quote(X:\swipl\bin) -llibswipl
LIBS += -L$$quote(X:\swipl\lib) -llibswipl
