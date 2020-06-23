QT += core testlib
QT += gui
QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../../src/common

SOURCES +=  tst_evt2spedataconverter.cpp


SOURCES += \
        ../../src/common/ZEvt2SpeConverter.cpp \
        ../../src/common/ZEvt2SpeDataConverter.cpp \


HEADERS += \
    ../../src/common/ZEvt2SpeConverter.h \
    ../../src/common/ZEvt2SpeDataConverter.h

include( ../../common.pri )
include( ../../app.pri )


