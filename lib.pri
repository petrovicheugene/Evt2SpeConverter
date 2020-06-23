#------------------------------------------------- 
DESTDIR = $${LIBS_PATH}/ 

win32: { 
DLLDESTDIR = $${BIN_PATH}/ 
CONFIG += skip_target_version_ext 
} 

unix: { 
CONFIG += unversioned_libname 
} 

 copyFiles($${TRANSLATIONS_PATH}/*.qm, $${LIBS_TRANSLATIONS_PATH}) 

