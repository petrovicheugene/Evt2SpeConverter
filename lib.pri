#------------------------------------------------- 
CONFIG(debug, debug|release) {
   TARGET = $$TARGET$${LIB_SUFFIX}
}

DESTDIR = $${LIBS_PATH}/

win32: { 
#DLLDESTDIR = $${BIN_PATH}/
CONFIG += skip_target_version_ext 
} 

unix: { 
CONFIG += unversioned_libname 
} 

preCopyFiles($${_PRO_FILE_PWD_}/*.h, $${EXPORT_PATH}/)
postCopyFiles($${LIBS_PATH}/$${TARGET}.*, $${BIN_PATH}/)

CONFIG(release, debug|release) {
   postCopyFiles($${TRANSLATIONS_PATH}/*.qm, $${BIN_PATH}/translations/)
}
