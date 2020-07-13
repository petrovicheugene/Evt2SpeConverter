//==========================================================
#include "ZEvt2SpeConverter.h"
#include "ZEvtContextConverterSettingsManager.h"
#include "ZVariableManager.h"
#include "ZWinPathValidator.h"

#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <QTextStream>

//==========================================================
ZEvt2SpeConverter::ZEvt2SpeConverter(QObject* parent) : QObject(parent)
{
    zv_spectrumDataExtractor = nullptr;
    zv_speHeaderLineNumber = 20;
}
//==========================================================
ZEvt2SpeConverter::ZEvt2SpeConverter(ZEvtSpectrumDataExtractor* converter, QObject* parent)
{
    zv_spectrumDataExtractor = nullptr;
    zv_speHeaderLineNumber = 20;
    zp_setSpectrumDataExtractor(converter);
}
//==========================================================
void ZEvt2SpeConverter::zp_setSpectrumDataExtractor(ZEvtSpectrumDataExtractor* extractor)
{
    if (zv_spectrumDataExtractor)
    {
        delete zv_spectrumDataExtractor;
    }

    zv_spectrumDataExtractor = extractor;
    zv_spectrumDataExtractor->setParent(this);
}
//==========================================================
QString ZEvt2SpeConverter::zp_errorString() const
{
    return zv_errorString;
}
//==========================================================
void ZEvt2SpeConverter::zp_convertFiles(const QStringList& filePathList)
{
    for (int i = 0; i < filePathList.count(); ++i)
    {
        if (!zh_convertFile(filePathList.at(i)))
        {
            QString msg = tr("Cannot convert file \"%1\". %2")
                              .arg(filePathList.at(i), zv_errorString);
            //
            if (filePathList.count() > 1)
            {
                if (QMessageBox::critical(nullptr,
                                          tr("Evt2Spe error"),
                                          msg + tr("\nDo you want to continue?"),
                                          QMessageBox::Yes,
                                          QMessageBox::No)
                    == QMessageBox::No)
                {
                    break;
                }
            }
            else
            {
                QMessageBox::critical(nullptr, tr("Evt2Spe error"), msg, QMessageBox::Ok);
            }
        }
    }
}
//==========================================================
bool ZEvt2SpeConverter::zh_convertFile(const QString& evtFilePath)
{
    if (!zv_spectrumDataExtractor)
    {
        zv_errorString = (tr("The data converter class Evt into Spe is not installed!"));
        return false;
    }

    zv_errorString.clear();
    // get data from src file
    QFile evtFile(evtFilePath);
    qint64 fileSize = evtFile.size();
    if (fileSize < 1)
    {
        zv_errorString = (tr("The file \"%1\" is empty!"));
        return false;
    }

    if (!evtFile.open(QIODevice::ReadOnly))
    {
        zv_errorString = (tr("Cannot open source file \"%1\" with error: %2.")
                              .arg(evtFilePath, evtFile.errorString()));
        return false;
    }

    QDataStream evtStream(&evtFile);
    QStringList speData;
    zv_spectrumDataExtractor->zp_convert(evtStream, speData);

    evtFile.close();

    QStringList speHeader;
    zh_createSpeHeader(speHeader);
    speData = speHeader + speData;

    QString speFilePath = zh_targetFile(evtFilePath);

    QFile speFile(speFilePath);
    if (!speFile.open(QIODevice::WriteOnly))
    {
        zv_errorString = (tr("Cannot open target file \"%1\" with error: %2.")
                              .arg(speFilePath, speFile.errorString()));
        return false;
    }

    QTextStream speStream(&speFile);
    foreach (QString line, speData)
    {
        speStream << line;
    }
    speFile.close();

    return true;
}
//==========================================================
void ZEvt2SpeConverter::zh_createSpeHeader(QStringList& headerStringList) const
{
    headerStringList.clear();

    headerStringList << "Converted from .evt";
    for (int i = 1; i < zv_speHeaderLineNumber; ++i)
    {
        headerStringList << QString("%1\n").arg(QString::number(0));
    }
}
//==========================================================
QString ZEvt2SpeConverter::zh_targetFile(const QString& evtFilePath)
{
    ZEvtContextConverterSettingsManager manager;
    // target fileName
    QFileInfo evtFileInfo(evtFilePath);
    ZVariableManager variableManager;
    QString speFileName = variableManager
                              .zp_createFileNameFromTemplate(manager.zp_outputFileNameTemplate(),
                                                             QFileInfo(evtFilePath).baseName());

    QString outputFolderPath = manager.zp_outputFolderPath();

    QDir evtFileDir(evtFileInfo.absolutePath());

    QString absOutputFolderPath;
    ZWinPathValidator winPathValidator;
    ZWinPathValidator::PathType pathType = winPathValidator.zp_validatePath(outputFolderPath);
    switch (pathType)
    {
    case ZWinPathValidator::PT_ABSOLUTE:
        absOutputFolderPath = outputFolderPath;
        break;
    case ZWinPathValidator::PT_RELATIVE:
        absOutputFolderPath = evtFileDir.cleanPath(evtFileDir.absoluteFilePath(outputFolderPath));
        break;
    case ZWinPathValidator::PT_INVALID:
    default:
        absOutputFolderPath = evtFileDir.cleanPath(
            evtFileDir.absoluteFilePath(variableManager.zp_defaultOutputPath()));
        break;
    }

    QDir targetDir;
    targetDir.mkpath(absOutputFolderPath);
    targetDir.cd(absOutputFolderPath);
    QString speFilePath = targetDir.absoluteFilePath(speFileName);

    return speFilePath;
}
//==========================================================
