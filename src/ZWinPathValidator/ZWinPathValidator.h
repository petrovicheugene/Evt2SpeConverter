//======================================================
#ifndef ZWINPATHVALIDATOR_H
#define ZWINPATHVALIDATOR_H
//======================================================
#include "ZWinPathValidator_global.h"
#include <QRegExp>
//======================================================

//======================================================
class ZWINPATHVALIDATOR_EXPORT ZWinPathValidator
{
public:
    ZWinPathValidator();
    enum PathType
    {
        PT_INVALID = 0,
        PT_ABSOLUTE = 1,
        PT_RELATIVE = 2
    };

    PathType zp_validatePath(const QString& path);
    bool zp_validateFileName(const QString& fileName);
    QString zp_error() const;

protected:
    // VARS
    QRegExp zv_pathRx;
    QRegExp zv_doubleSlashRx;
    QRegExp zv_absolutePathRx;
    QRegExp zv_fileNameRx;
    QString zv_error;
    // FUNCS
    void zh_createComponents();
};
//======================================================
#endif // ZWINPATHVALIDATOR_H
