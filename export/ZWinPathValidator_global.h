#ifndef ZWINPATHVALIDATOR_GLOBAL_H
#define ZWINPATHVALIDATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZWINPATHVALIDATOR_LIBRARY)
#  define ZWINPATHVALIDATOR_EXPORT Q_DECL_EXPORT
#else
#  define ZWINPATHVALIDATOR_EXPORT Q_DECL_IMPORT
#endif

#endif // ZWINPATHVALIDATOR_GLOBAL_H