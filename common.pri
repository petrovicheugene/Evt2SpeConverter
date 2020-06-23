#------------------------------------------------- 
PROJECT_ROOT_PATH = $${PWD}/ 

win32: OS_SUFFIX = win32 
linux-g++: OS_SUFFIX = linux 

CONFIG += c++11 
CONFIG += c++14 
CONFIG += c++17 

VERSION=$${VER_MAJ}.$${VER_MIN}.$${VER_PAT} 

CONFIG(debug, debug|release) { 
    BUILD_FLAG = debug 
    LIB_SUFFIX = d 
} else { 
    BUILD_FLAG = release 
} 

#Define the preprocessor macro to get the application version in the application. 
DEFINES += APP_DISPLAY_NAME=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\" 
DEFINES += APP_PRODUCT=\"\\\"$${TARGET}\\\"\" 
DEFINES += APP_VERSION=\"\\\"$${VERSION}.$${VER_RELEASE}\\\"\" 
DEFINES += APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\" 
DEFINES += APP_COMPANY_URL=\"\\\"$${COMPANY_URL}\\\"\" 
DEFINES += APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\" 
DEFINES += APP_ICON=\"\\\"$${RC_ICONS}\\\"\" 
DEFINES += APP_DESCRIPTION=\"\\\"$${QMAKE_TARGET_DESCRIPTION}\\\"\" 

#DEBUG SETTINGS 
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT 
#by default defined: in Debug mode QT_DEBUG, in Release mode QT_NO_DEBUG 

SRC_PATH = $${PROJECT_ROOT_PATH}/src/ 
LIBS_PATH = $${PROJECT_ROOT_PATH}/lib.$${OS_SUFFIX}/ 
EXPORT_PATH = $${PROJECT_ROOT_PATH}/export/ 
IMPORT_PATH = $${PROJECT_ROOT_PATH}/import/ 
COMMON_PATH = $${SRC_PATH}/common/ 
TRANSLATIONS_PATH = $${PROJECT_ROOT_PATH}/translations/$${TARGET}/ 
BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/$${TARGET}/ 
mkpath($${SRC_PATH}) 
mkpath($${LIBS_PATH}) 
mkpath($${EXPORT_PATH}) 
mkpath($${IMPORT_PATH}) 
mkpath($${COMMON_PATH}) 
mkpath($${TRANSLATIONS_PATH}) 
mkpath($${BIN_PATH}) 

BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/ 
RCC_DIR = $${BUILD_PATH}/rcc/ 
UI_DIR = $${BUILD_PATH}/ui/ 
MOC_DIR = $${BUILD_PATH}/moc/ 
OBJECTS_DIR = $${BUILD_PATH}/obj/ 
mkpath($${BUILD_PATH}) 
mkpath($${RCC_DIR}) 
mkpath($${UI_DIR}) 
mkpath($${MOC_DIR}) 
mkpath($${OBJECTS_DIR}) 

LIBS += -L$${LIBS_PATH}/ 
INCLUDEPATH += $${EXPORT_PATH}/ 
INCLUDEPATH += $${IMPORT_PATH}/ 
INCLUDEPATH += $${COMMON_PATH}/ 

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter 

# FUNCS 
# creates translation file names for languages from LANGUAGES variable 
defineReplace(prependAll) { 
 for(a,$$1):result += $$2$${a}$$3 
 return($$result) 
} 

# Copies the given files to the given directory 
defineTest(copyFiles) { 
    files = $$1 
    DDIR = $$2 

    for(FILE, files) { 
        # Replace slashes in paths with backslashes for Windows 
        win32:FILE ~= s,/,\\,g 
        win32:DDIR ~= s,/,\\,g 

        isEmpty(QMAKE_POST_LINK){ 
        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t) 
        }else{ 
        QMAKE_POST_LINK += & $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t) 
        } 
    } 
    export(QMAKE_POST_LINK) 
} 

TRANSLATIONS = $$prependAll(LANGUAGES, $${TRANSLATIONS_PATH}/$${TARGET}_, .ts) 
QMAKE_PRE_LINK += $$(QTDIR)/bin/lupdate-pro $${_PRO_FILE_} 

CONFIG(release, debug|release) { 
    QMAKE_PRE_LINK += & $$(QTDIR)/bin/lrelease-pro $${_PRO_FILE_} 
} 

linux-g++: QMAKE_CXXFLAGS += -std=c++11 
linux-g++: QMAKE_CXXFLAGS += -std=c++14 
linux-g++: QMAKE_CXXFLAGS += -std=c++17 

