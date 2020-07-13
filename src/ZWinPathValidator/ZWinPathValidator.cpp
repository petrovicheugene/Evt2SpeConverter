//======================================================
#include "ZWinPathValidator.h"
#include <QObject>
//======================================================
ZWinPathValidator::ZWinPathValidator()
{
    zh_createComponents();
}
//======================================================
ZWinPathValidator::PathType ZWinPathValidator::zp_validatePath(const QString& path)
{
    zv_error.clear();
    if (!zv_pathRx.exactMatch(path))
    {
        zv_error = QObject::tr("The path string doesn't match the valid windows path.");
        return ZWinPathValidator::PT_INVALID;
    }

    if (zv_doubleSlashRx.indexIn(path) >= 0)
    {
        zv_error = QObject::tr("The string has a double slash.");
        return ZWinPathValidator::PT_INVALID;
    }

    if (zv_absolutePathRx.exactMatch(path))
    {
        return ZWinPathValidator::PT_ABSOLUTE;
    }
    else
    {
        return ZWinPathValidator::PT_RELATIVE;
    }
}
//======================================================
bool ZWinPathValidator::zp_validateFileName(const QString& fileName)
{
    zv_error.clear();
    if (!zv_fileNameRx.exactMatch(fileName))
    {
        zv_error = QObject::tr("The file name contains unacceptable symbols: %1.")
                       .arg("^\\/|;:%<>+*&");
        return false;
    }

    return true;
}
//======================================================
QString ZWinPathValidator::zp_error() const
{
    return zv_error;
}
//======================================================
void ZWinPathValidator::zh_createComponents()
{
    QString device = QString("((((%1)|(%2))(%3))|((%2{2,2}%3){1,}))")
                         .arg("[a-zA-Z]:", "[.]", "[\\\\/]");
    QString requiredSlash = "([\\\\/]{1,1})";
    QString unrequiredSlash = "([\\\\/]{0,1})";
    QString commaDot = "([.,]{0,})";
    QString pathSymbols = "([^.,\\\\/|:%;<>+*&]{1,})";
    QString absolutePathRxString = QString("^[a-zA-Z]:[\\\\/].*$");

    QString pathRxString = QString("^(%1{0,1})(((%2%3){1,}%2){0,1})((%4(%2%3){1,}%2){0,})(%5)$")
                               .arg(device, commaDot, pathSymbols, requiredSlash, unrequiredSlash);

    QString doubleSlashRxString = "([\\\\/]{2,})";

    zv_pathRx = QRegExp(pathRxString);
    zv_doubleSlashRx = QRegExp(doubleSlashRxString);
    zv_absolutePathRx = QRegExp(absolutePathRxString);

    QString fileNameSymbols = "([^\\\\/|:%;<>+*&]{1,})";
    zv_fileNameRx = QRegExp(fileNameSymbols);
}
//======================================================
