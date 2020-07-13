QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = evt2speSettings

#PRO VARS
#Application version
RC_ICONS = "e2s-1.ico"

VER_MAJ=1
VER_MIN=0
VER_PAT=0

QMAKE_TARGET_PRODUCT="Evt2Spe Context Settings"
QMAKE_TARGET_DESCRIPTION="Settings manager for evt2spe application"
QMAKE_TARGET_COMPANY="TechnoAnalyt"
QMAKE_TARGET_COPYRIGHT="Copyright © $${QMAKE_TARGET_COMPANY} Ltd. 2020.  All rights reserved."
COMPANY_URL=tehnoanalit.com
LANGUAGES += en \
    ru \
    kk
#-------------------------------------------------
# in common.pri will be defined VERSION, TARGET, DEBUG SETTINGS
#  global APP DEFINES
#-------------------------------------------------
include( ../../common.pri )
include( ../../app.pri )

#END


CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += "C:/Boost/1730-64/include"
INCLUDEPATH += ..\..\src\common\ZBaseMainWindow

SOURCES += \
    ../common/ZBaseMainWindow/ZBaseMainWindow.cpp \
    ../common/ZBaseMainWindow/ZHelpBrowser.cpp \
    ../common/ZBaseMainWindow/ZTranslatorManager.cpp \
    ../common/ZEvt2SpeSettingsWidget.cpp \
    ../common/ZEvtContextConverterSettingsManager.cpp \
    ../common/ZVariableManager.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ../common/ZBaseMainWindow/ZBaseMainWindow.h \
    ../common/ZBaseMainWindow/ZHelpBrowser.h \
    ../common/ZBaseMainWindow/ZTranslatorManager.h \
    ../common/ZEvt2SpeSettingsWidget.h \
    ../common/ZEvtContextConverterSettingsManager.h \
    ../common/ZVariableManager.h \
    MainWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../common/ZBaseMainWindow/HelpBrowserResources.qrc \
    resources.qrc

DISTFILES += \
    ../common/ZBaseMainWindow/blue_home.ico \
    ../common/ZBaseMainWindow/blue_home.png \
    ../common/ZBaseMainWindow/blue_left.ico \
    ../common/ZBaseMainWindow/blue_left.png \
    ../common/ZBaseMainWindow/blue_right.ico \
    ../common/ZBaseMainWindow/blue_right.png \
    ../common/ZBaseMainWindow/editclear.png \
    ../common/ZBaseMainWindow/green_home.ico \
    ../common/ZBaseMainWindow/green_home.png \
    ../common/ZBaseMainWindow/green_left.ico \
    ../common/ZBaseMainWindow/green_left.png \
    ../common/ZBaseMainWindow/green_right.ico \
    ../common/ZBaseMainWindow/green_right.png
