//==========================================================
#include "ZEvt2SpeConverter.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
//==========================================================
ZEvt2SpeConverter::ZEvt2SpeConverter(QObject* parent) : QObject(parent)
{
    zv_converter = nullptr;
}
//==========================================================
ZEvt2SpeConverter::ZEvt2SpeConverter(ZEvt2SpeDataConverter* converter,
                                     QObject* parent)
{
    zv_converter = nullptr;
    zp_setDataConverter(converter);
}
//==========================================================
void ZEvt2SpeConverter::zp_setDataConverter(ZEvt2SpeDataConverter* converter)
{
    if (zv_converter)
    {
        delete zv_converter;
    }

    zv_converter = converter;
    zv_converter->setParent(this);
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
            QString msg = tr("Cannot convert file \"%1\". Error: \"%2\".")
                              .arg(filePathList.at(i), zv_errorString);
            if (QMessageBox::question(nullptr,
                                      tr("Evt2Spe error"),
                                      msg,
                                      QMessageBox::Yes,
                                      QMessageBox::No)
                == QMessageBox::No)
            {
                break;
            }
        }
    }
}
//==========================================================
bool ZEvt2SpeConverter::zh_convertFile(const QString& evtFilePath)
{
    if (!zv_converter)
    {
        zv_errorString = (tr(
            "The data converter class Evt into Spe is not installed!"));
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
        zv_errorString = (tr("Cannot open file \"%1\"!\nThe error is: \"%2\".")
                              .arg(evtFilePath, evtFile.errorString()));
        return false;
    }

    QDataStream evtStream(&evtFile);
    QStringList speData;
    zv_converter->zp_convert(evtStream, speData);

    evtFile.close();

    qDebug() << speData;

    // put converted  data into target .Spe file
    QFileInfo fi(evtFilePath);
    QString speFilePath = fi.path() + "/" + fi.completeBaseName() + ".spe";

    QFile speFile(speFilePath);
    if (!speFile.open(QIODevice::WriteOnly))
    {
        zv_errorString = (tr("Cannot open file \"%1\"!\nThe error is: \"%2\".")
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
