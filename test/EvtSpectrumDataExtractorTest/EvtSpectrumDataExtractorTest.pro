QT += core testlib
QT += gui
QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH += ../../src/common

SOURCES +=  \
      #  ../../src/common/ZEvt2SpeConverter.cpp \
        ../../src/common/ZEvtSpectrumDataExtractor.cpp \
    Test_EvtSpectrumDataExtractor.cpp

HEADERS += \
    #../../src/common/ZEvt2SpeConverter.h \
    ../../src/common/ZEvtSpectrumDataExtractor.h

include( ../../common.pri )
include( ../../app.pri )


