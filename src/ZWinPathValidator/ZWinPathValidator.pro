QT -= gui

TEMPLATE = lib
DEFINES += ZWINPATHVALIDATOR_LIBRARY

TARGET = ZWinPathValidator

#PRO VARS
#Application version
#RC_ICONS = "ZImages/SRVLab-8.ico"

VER_MAJ=1
VER_MIN=0
VER_PAT=0

QMAKE_TARGET_PRODUCT="WinPathValidator"
QMAKE_TARGET_DESCRIPTION="Win Path Validator"
QMAKE_TARGET_COMPANY="TechnoAnalyt"
QMAKE_TARGET_COPYRIGHT="Copyright © $${QMAKE_TARGET_COMPANY} Ltd. 2020. All rights reserved."
COMPANY_URL=tehnoanalit.com
LANGUAGES += en \
    ru \
    kk
#-------------------------------------------------
# in common.pri will be defined VERSION, TARGET, DEBUG SETTINGS
#  global APP DEFINES
#-------------------------------------------------
include( ../../common.pri )
include( ../../lib.pri )

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

SOURCES += \
    ZWinPathValidator.cpp

HEADERS += \
    ZWinPathValidator_global.h \
    ZWinPathValidator.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
