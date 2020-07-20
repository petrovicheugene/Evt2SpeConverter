QT -= gui
QT += widgets

#PRO VARS
TARGET = evt2spe
#Application version
#RC_ICONS = "ZImages/SRVLab-8.ico"
CONFIG += c++11
VER_MAJ=2
VER_MIN=0
VER_PAT=0

QMAKE_TARGET_PRODUCT="Evt2Spe"
QMAKE_TARGET_DESCRIPTION="Evt to spe converter"
QMAKE_TARGET_COMPANY="TechnoAnalyt"
QMAKE_TARGET_COPYRIGHT="Copyright © $${QMAKE_TARGET_COMPANY} Ltd. 2020.  All rights reserved."
COMPANY_URL=tehnoanalit.com

#-------------------------------------------------
# in common.pri will be defined VERSION, TARGET, DEBUG SETTINGS
#  global APP DEFINES
#-------------------------------------------------
include( ../../common.pri )
include( ../../app.pri )

#END

CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ../common

SOURCES += \
        ../common/ZEvt2SpeConverter.cpp \
        ../common/ZEvtContextConverterSettingsManager.cpp \
        ../common/ZEvtSpectrumDataExtractor.cpp \
        ../common/ZVariableManager.cpp \
        main.cpp

HEADERS += \
    ../common/ZEvt2SpeConverter.h \
    ../common/ZEvtContextConverterSettingsManager.h \
    ../common/ZEvtSpectrumDataExtractor.h \
    ../common/ZVariableManager.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

