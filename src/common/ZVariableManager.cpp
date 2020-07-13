//======================================================
#include "ZVariableManager.h"
#include "ZWinPathValidator.h"

#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QTime>

#include <QMessageBox>
//======================================================
ZVariableManager::ZVariableManager(QObject* parent) : QObject(parent)
{
    zv_variables << "filename";
    zv_variables << "date";
    zv_variables << "time";

    zv_defaultOutputPath = "./SPE/";
    zv_defaultOutputFileNameTemplate = "%" + zv_variables.at(0) + "%.spe";
}
//======================================================
QString ZVariableManager::zp_defaultOutputPath()
{
    return zv_defaultOutputPath;
}
//======================================================
QString ZVariableManager::zp_defaultFileNameTemplate()
{
    return zv_defaultOutputFileNameTemplate;
}
//======================================================
QStringList ZVariableManager::zp_variableList() const
{
    return zv_variables;
}
//======================================================
bool ZVariableManager::zp_checkFileNameTemplate(const QString& fileNameTemplate)
{
    zv_error.clear();
    bool insidePercent = false;
    QString currentVar;
    foreach (QChar ch, fileNameTemplate)
    {
        if (ch == '%')
        {
            if (insidePercent)
            {
                // compare current var to existing ones
                if (!zv_variables.contains(currentVar))
                {
                    zv_error = tr("Wrong variable \"%1\"").arg(currentVar);
                    return false;
                }
                else
                {
                    currentVar.clear();
                }
            }

            insidePercent = !insidePercent;
            continue;
        }
        else
        {
            if (insidePercent)
            {
                currentVar.append(ch);
            }
        }
    } // end foreach

    if (insidePercent)
    {
        zv_error = tr("The wrong variable defining \"%1\"").arg(currentVar);
        return false;
    }

    QString newFileName = zp_createFileNameFromTemplate(fileNameTemplate, "filename");
    ZWinPathValidator winPathValidator;
    if (!winPathValidator.zp_validateFileName(newFileName))
    {
        zv_error = winPathValidator.zp_error();
        return false;
    }

    return true;
}
//======================================================
QString ZVariableManager::zp_createFileNameFromTemplate(const QString& fileNameTemplate,
                                                        const QString& srcFileName)
{
    QString newFileName = fileNameTemplate;
    newFileName.replace(zh_braceVariable(zv_variables.at(0)), srcFileName);
    newFileName.replace(zh_braceVariable(zv_variables.at(1)),
                        QDate::currentDate().toString(Qt::ISODate));
    newFileName.replace(zh_braceVariable(zv_variables.at(2)),
                        QTime::currentTime().toString("hh.mm.ss"));

    return newFileName;
}
//======================================================
QString ZVariableManager::zh_braceVariable(const QString& variable)
{
    return "%" + variable + "%";
}
//======================================================
QString ZVariableManager::zp_error() const
{
    return zv_error;
}
//======================================================
